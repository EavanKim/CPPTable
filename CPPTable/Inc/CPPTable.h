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
using eChar_t		= char;
using eChar_p		= char*;
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
		int size = strlen(_char);
		m_data.s_ = new	eChar_t[size];
		memcpy_s(m_data.s_, size, _char, size);
	}

	IEntity(IEntity& _entity)
		: m_type(_entity.m_type)
		, m_data(_entity.m_data)
	{

	}

	~IEntity()
	{
		switch (m_type)
		{
		case ERTTI::ERTTI_STRING : delete[] m_data.s_;
		}
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
		int size = strlen(_data);
		m_data.s_ = new	eChar_t[size + 1];
		memcpy_s(m_data.s_, size, _data, size);
		m_data.s_[size] = '\0';
		return m_data.s_;
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
			tokens.emplace_back(std::move(token));
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