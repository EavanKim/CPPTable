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

#include <exception>

#include "Define_CPPTable.h"

// 주의, 32비트로 만들고 64비트 호환모드로 사용하면 메모리가 절삭될 수 있습니다.
// 반드시 타겟 아키텍처를 일치시켜서 사용하세요.

#if _WIN64
using INTPTR = uint64_t;
#elif _WIN32
using INTPTR = uint32_t;
#endif

template<typename T>
struct IPTR
{
public:
	IPTR()
	{

	}

	IPTR(T* _ptr, bool _dispose = false)
		: ptr_(_ptr)
		, disposePtr_(_dispose)
	{

	}

	IPTR(INTPTR _int, bool _dispose = false)
		: ptr_((T*)_int)
		, disposePtr_(_dispose)
	{

	}

	virtual ~IPTR()
	{
		if ((nullptr != ptr_) && disposePtr_)
		{
			delete ptr_;
			ptr_ = nullptr;
		}
	}

	T* operator->()
	{
		return ptr_;
	}

	INTPTR operator*()
	{
		return (INTPTR)ptr_;
	}

	INTPTR operator=(INTPTR _int)
	{
		if ((nullptr != ptr_) && disposePtr_)
		{
			delete ptr_;
			ptr_ = nullptr;
		}

		ptr_ = (INTPTR)_int;
		return ptr_;
	}

	T* operator=(T* _ptr)
	{
		if ((nullptr != ptr_) && disposePtr_)
		{
			delete ptr_;
			ptr_ = nullptr;
		}

		ptr_ = _ptr;
		return ptr_;
	}

private:
	bool disposePtr_ = false;
	T* ptr_ = nullptr;
};


typedef unsigned char EBYTE;

__forceinline INTPTR ParsePtr(void* _ptr)
{
	return (INTPTR)_ptr;
}

__forceinline INTPTR ParsePtr(EBYTE* _ptr)
{
	return (INTPTR)_ptr;
}

__forceinline void* ParsePtr(INTPTR _int)
{
	return (void*)_int;
}

typedef unsigned long memSize_t;
typedef unsigned long memIndex_t;
typedef unsigned long columnId_t;
typedef unsigned long primaryId_t;

using eDateTime_t	= std::chrono::high_resolution_clock::time_point;
using eFloat_t		= double;
using eStr_t		= std::string;
using eInt_t		= int64_t;

enum ERTTI
{
	ERTTI_UNKNOWN,
	ERTTI_DATETIME,
	ERTTI_INT,
	ERTTI_FLOAT,
	ERTTI_STRING,
	ERTTI_MAX
};

// 동적 사이즈를 사용하는 문자열 관련 처리는 EMemory에서 대부분 처리하기
// 자신의 타입정보를 기록하고 반환할 때는 m_type대로 처리해서 돌려줍니다.
// 데이터 자체는 링크드 리스트로 관리하고,
// 테이블에서의 데이터 위치는 키값으로 처리합니다.
struct CPPTABLE_API EListValue
{
	EListValue(ERTTI _rtti, columnId_t _x, primaryId_t _y, EListValue* _prev, EListValue* _next)
		: m_type(_rtti)
		, m_column(_x)
		, m_row(_y)
		, m_prev(_prev)
		, m_next(_next)
	{
		
	}



	ERTTI m_type = ERTTI::ERTTI_UNKNOWN;
	columnId_t m_column = 0;
	primaryId_t m_row = 0;
	EListValue* m_prev = nullptr;
	EListValue* m_next = nullptr;
};

struct CPPTABLE_API EListValue_DATETIME : EListValue
{
	EListValue_DATETIME(columnId_t _x, primaryId_t _y, EListValue* _prev, EListValue* _next)
		: EListValue(ERTTI::ERTTI_DATETIME, _x, _y, _prev, _next)
	{

	}

	EListValue_DATETIME(columnId_t _x, primaryId_t _y, EListValue* _prev, EListValue* _next, eDateTime_t _init)
		: EListValue(ERTTI::ERTTI_DATETIME, _x, _y, _prev, _next)
		, m_data(_init)
	{

	}

	eDateTime_t m_data = std::chrono::high_resolution_clock::now();
};

struct CPPTABLE_API EListValue_INT : EListValue
{
	EListValue_INT(columnId_t _x, primaryId_t _y, EListValue* _prev, EListValue* _next)
		: EListValue(ERTTI::ERTTI_INT, _x, _y, _prev, _next)
	{

	}

	EListValue_INT(columnId_t _x, primaryId_t _y, EListValue* _prev, EListValue* _next, eInt_t _init)
		: EListValue(ERTTI::ERTTI_INT, _x, _y, _prev, _next)
		, m_data(_init)
	{

	}

	eInt_t m_data = 0;
};

struct CPPTABLE_API EListValue_FLOAT : EListValue
{
	EListValue_FLOAT(columnId_t _x, primaryId_t _y, EListValue* _prev, EListValue* _next)
		: EListValue(ERTTI::ERTTI_FLOAT, _x, _y, _prev, _next)
	{

	}

	EListValue_FLOAT(columnId_t _x, primaryId_t _y, EListValue* _prev, EListValue* _next, eFloat_t _init)
		: EListValue(ERTTI::ERTTI_FLOAT, _x, _y, _prev, _next)
		, m_data(_init)
	{

	}

	// 4byte가 될 수 있으므로 작은 수 기준으로 선언합니다.
	eFloat_t m_data = 0.f;
};

struct CPPTABLE_API EListValue_STRING : EListValue
{
	EListValue_STRING(columnId_t _x, primaryId_t _y, EListValue* _prev, EListValue* _next)
		: EListValue(ERTTI::ERTTI_STRING, _x, _y, _prev, _next)
	{

	}

	EListValue_STRING(columnId_t _x, primaryId_t _y, EListValue* _prev, EListValue* _next, eStr_t _init)
		: EListValue(ERTTI::ERTTI_STRING, _x, _y, _prev, _next)
		, m_data(_init)
	{

	}

	eStr_t m_data = "";
};

__forceinline std::vector<std::string> StrSplit(const std::string& _string, char _split)
{
	std::vector<std::string> tokens;
	std::string token;
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

#include "EMemoryBlock.h"
#include "EMemoryPool.h"

#include "ESchema.h"
#include "ERow.h"
#include "ETable.h"

#endif