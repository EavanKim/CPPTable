#ifndef	CPPTABLE_H__
#define CPPTABLE_H__

#include <cstdint>
#include <memory>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <ctime>
#include <chrono>
#include <string>
#include <sstream>

#include <filesystem>

#include <exception>

// 주의, 32비트로 만들고 64비트 호환모드로 사용하면 메모리가 절삭될 수 있습니다.
// 반드시 타겟 아키텍처를 일치시켜서 사용하세요.

#if _WIN64
using INTPTR = uint64_t;
#elif _WIN32
using INTPTR = uint32_t;
#endif

typedef unsigned long memSize_t;
typedef unsigned long memIndex_t;
typedef unsigned long columnId_t;
typedef unsigned long primaryId_t;

//using eDateTime_t	= std::chrono::high_resolution_clock::time_point;
using eDateTime_t	= uint64_t;
using eFloat_t		= double;
using eStr_t		= std::string;
using eInt_t		= int64_t;
using EBYTE			= unsigned char;

enum ERTTI
{
	ERTTI_UNKNOWN,
	ERTTI_DATETIME,
	ERTTI_INT,
	ERTTI_FLOAT,
	ERTTI_STRING,
	ERTTI_MAX
};

struct IEntity
{
	IEntity(ERTTI _type)
		: m_type(_type)
	{

	}

	virtual void PrintDataToBuffer() = 0;

	ERTTI m_type = ERTTI::ERTTI_UNKNOWN;
};

struct Entity_Int : public IEntity
{
	Entity_Int()
		: IEntity(ERTTI::ERTTI_INT)
		, m_data(0)
	{

	}

	Entity_Int(eInt_t _data)
		: IEntity(ERTTI::ERTTI_INT)
		, m_data(_data)
	{

	}

	Entity_Int(IEntity* _entity)
		: IEntity(ERTTI::ERTTI_INT)
		, m_data(0)
	{
		switch (_entity->m_type)
		{
		case ERTTI::ERTTI_DATETIME:
			m_data = static_cast<Entity_Datetime*>(_entity)->m_data;
			break;
		case ERTTI::ERTTI_INT:
			m_data = static_cast<Entity_Int*>(_entity)->m_data;
			break;
		case ERTTI::ERTTI_FLOAT:
			m_data = static_cast<eInt_t>(static_cast<Entity_Float*>(_entity)->m_data);
			break;
		}
	}

	virtual void PrintDataToBuffer()
	{
		vfprintf();
	}

	eInt_t m_data;
};

struct Entity_Float : public IEntity
{
	Entity_Float()
		: IEntity(ERTTI::ERTTI_FLOAT)
		, m_data(0)
	{

	}

	Entity_Float(float _data)
		: IEntity(ERTTI::ERTTI_FLOAT)
		, m_data(_data)
	{

	}

	Entity_Float(eFloat_t _data)
		: IEntity(ERTTI::ERTTI_FLOAT)
		, m_data(_data)
	{

	}

	Entity_Float(IEntity* _entity)
		: IEntity(ERTTI::ERTTI_FLOAT)
		, m_data(0)
	{
		switch (_entity->m_type)
		{
		case ERTTI::ERTTI_INT:
			m_data = static_cast<eFloat_t>(static_cast<Entity_Int*>(_entity)->m_data);
			break;
		case ERTTI::ERTTI_FLOAT:
			m_data = static_cast<Entity_Float*>(_entity)->m_data;
			break;
		}
	}

	virtual void PrintDataToBuffer()
	{

	}

	eFloat_t m_data;
};

struct Entity_Datetime : public IEntity
{
	Entity_Datetime()
		: IEntity(ERTTI::ERTTI_DATETIME)
		, m_data(0)
	{
		
	}

	Entity_Datetime(eDateTime_t _time)
		: IEntity(ERTTI::ERTTI_DATETIME)
		, m_data(_time)
	{

	}

	Entity_Datetime(time_t _time)
		: IEntity(ERTTI::ERTTI_DATETIME)
		, m_data(_time)
	{

	}

	Entity_Datetime(IEntity* _entity)
		: IEntity(ERTTI::ERTTI_DATETIME)
		, m_data(0)
	{
		switch (_entity->m_type)
		{
		case ERTTI::ERTTI_DATETIME:
			m_data = static_cast<Entity_Datetime*>(_entity)->m_data;
			break;
		case ERTTI::ERTTI_INT:
			m_data = static_cast<Entity_Int*>(_entity)->m_data;
			break;
		}
	}

	virtual void PrintDataToBuffer()
	{

	}

	eDateTime_t m_data;
};

struct Entity_String : public IEntity
{
	Entity_String()
		: IEntity(ERTTI::ERTTI_STRING)
		, m_blockLength(0)
		, m_data("")
	{

	}

	Entity_String(eStr_t _str)
		: IEntity(ERTTI::ERTTI_STRING)
		, m_blockLength(_str.size())
		, m_data(_str)
	{

	}

	Entity_String(IEntity* _entity)
		: IEntity(ERTTI::ERTTI_STRING)
		, m_blockLength(0)
		, m_data("")
	{
		switch (_entity->m_type)
		{
		case ERTTI::ERTTI_STRING:
			Entity_String* casting = static_cast<Entity_String*>(_entity);
			m_blockLength = casting->m_blockLength;
			m_data = casting->m_data;
			break;
		default:
			break;
		}
	}

	virtual void PrintDataToBuffer()
	{

	}

	// 저장할 때 문자열 배열 블럭길이 표시용 데이터입니다.
	eInt_t m_blockLength;

	//std::String은 동적 배열이 자체적으로 있다보니 저장할 때 그대로 사용되지 않고
	// std::vector<char[16]> 처럼 취급해서 저장합니다.
	eStr_t m_data;
};

__forceinline std::vector<std::string> StrSplit(const std::string& _string, char _split)
{
	std::vector<std::string> tokens;
	std::string token = "";
	token.reserve(_string.size());

	for (const char& ch : _string)
	{
		if (ch == _split)
		{
			tokens.emplace_back(std::move(token));
			continue;
		}

		token += ch;
	}

	return tokens;
}

#include "ESchema.h"
#include "ERow.h"
#include "ETable.h"

#endif