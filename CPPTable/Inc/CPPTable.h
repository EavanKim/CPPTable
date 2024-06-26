#ifndef	CPPTABLE_H__
#define CPPTABLE_H__

#include <cstdint>
#include <memory>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <list>
#include <ctime>
#include <chrono>
#include <string>
#include <sstream>

#include <fstream>

#include <filesystem>

#include <exception>

// 주의, 32비트로 만들고 64비트 호환모드로 사용하면 메모리가 절삭될 수 있습니다.
// 반드시 타겟 아키텍처를 일치시켜서 사용하세요.

#if _WIN64
using INTPTR = uint64_t;
#elif _WIN32
using INTPTR = uint32_t;
#endif

typedef unsigned long long memSize_t;
typedef unsigned long long memIndex_t;
typedef unsigned long long columnId_t;
typedef unsigned long long primaryId_t;
typedef unsigned long long strId_t;
#define NONE_STR_ID 0


//using eDateTime_t	= std::chrono::high_resolution_clock::time_point;
using eDateTime_t	= uint64_t;
using eFloat_t		= double;
using eChar_t		= char;
using eChar_p		= char*;
using eInt_t		= int64_t;
using EBYTE			= unsigned char;

struct eStrList_t
{
	strId_t m_id = NONE_STR_ID;
	std::shared_ptr<std::string> m_str;
};

struct eStr_t
{
	strId_t m_id = NONE_STR_ID;
	std::weak_ptr<std::string> m_str;
};

enum ENTITY_TYPE
{
	ENTITY_SCHEMA,
	ENTITY_ROW
};

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
public:
	IEntity()
		: m_type(ERTTI::ERTTI_UNKNOWN)
	{
		m_data.i_ = 0; // 널정리
	}

	IEntity(eInt_t _int)
		: m_type(ERTTI::ERTTI_INT)
	{
		m_data.i_ = _int;
	}

	IEntity(eFloat_t _float)
		: m_type(ERTTI::ERTTI_FLOAT)
	{
		m_data.f_ = _float;
	}

	IEntity(eDateTime_t _dateTime)
		: m_type(ERTTI::ERTTI_DATETIME)
	{
		m_data.d_ = _dateTime;
	}

	IEntity(eChar_p _char)
		: m_type(ERTTI::ERTTI_STRING)
	{
		int size = strlen(_char) + 1;
		size += (16 - (size & 15));
		m_data.s_ = new	eChar_t[size];
		memset(m_data.s_, 0x00, size);
		memcpy_s(m_data.s_, size, _char, size);
	}

	IEntity(IEntity& _entity)
		: m_type(_entity.m_type)
		, m_data(_entity.m_data)
	{

	}
	IEntity(IEntity* _entity)
		: m_type(_entity->m_type)
		, m_data(_entity->m_data)
	{

	}

	~IEntity()
	{
		Clear();
	}

	eInt_t operator=(eInt_t _data)
	{
		m_type = ERTTI::ERTTI_INT;
		m_data.i_ = _data;
		return m_data.i_;
	}

	eFloat_t operator=(eFloat_t _data)
	{
		m_type = ERTTI::ERTTI_FLOAT;
		m_data.f_ = _data;
		return m_data.f_;
	}

	eDateTime_t operator=(eDateTime_t _data)
	{
		m_type = ERTTI::ERTTI_DATETIME;
		m_data.d_ = _data;
		return m_data.d_;
	}

	eChar_p operator=(eChar_p _data)
	{
		m_type = ERTTI::ERTTI_STRING;
		int size = strlen(_data);
		m_data.s_ = new	eChar_t[size];
		memcpy_s(m_data.s_, size, _data, size);
		return m_data.s_;
	}

	eChar_p operator=(const char*&& _data)
	{
		m_type = ERTTI::ERTTI_STRING;
		int size = strlen(_data) + 1;
		size += (16 - (size & 15));
		m_data.s_ = new	eChar_t[size + 1];
		memcpy_s(m_data.s_, size, _data, size);
		m_data.s_[size] = '\0';
		return m_data.s_;
	}

	void Load(FILE* _fPtr)
	{
		Clear();


	}

	void Save(FILE* _fPtr)
	{
		switch (m_type)
		{
		case ERTTI::ERTTI_DATETIME:
			fprintf_s(_fPtr, "%08llX`%08llX;", ERTTI::ERTTI_DATETIME, m_data.d_);
			break;
		case ERTTI::ERTTI_INT:
			fprintf_s(_fPtr, "%08llX`%08llX;", ERTTI::ERTTI_INT, m_data.i_);
			break;
		case ERTTI::ERTTI_FLOAT:
			fprintf_s(_fPtr, "%08llX`%08llX;", ERTTI::ERTTI_INT, m_data.f_);
			break;
		case ERTTI::ERTTI_STRING:
			fprintf_s(_fPtr, "%08llX`%08llX`\"%s\";", ERTTI::ERTTI_STRING, strlen(m_data.s_), m_data.s_);
			break;
		}
	}

	std::string parse(FILE* _file, size_t& _seek, char _split = ';')
	{
		bool isSkip = false;
		char rHeaderBuffer[16];
		std::string token;
		fseek(_file, _seek, 0);

		size_t readHeaderSize = fread_s(rHeaderBuffer, 16, 16, 1, _file);
		_seek += readHeaderSize;



		//while (const char& ch : _string)
		//{
		//	if ('\"' == ch)
		//	{
		//		isSkip != isSkip;
		//	}

		//	if (!isSkip && ch == _split)
		//	{
		//		break;
		//	}

		//	token += ch;
		//}

		return token;
	}

	void Clear()
	{
		switch (m_type)
		{
		case ERTTI::ERTTI_STRING: if (nullptr != m_data.s_) delete[] m_data.s_; m_data.s_ = nullptr;
		}
		
		m_type = ERTTI::ERTTI_UNKNOWN;
		m_data.i_ = 0;
	}

	ERTTI m_type;
	union binaryData
	{
		eInt_t i_;
		eFloat_t f_;
		eDateTime_t d_;
		eChar_p s_;
	} m_data;
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
			tokens.push_back(std::move(token));
			continue;
		}

		token += ch;
	}

	return tokens;
}

#include "ERow.h"
#include "ESchema.h"
#include "ETable.h"

#endif