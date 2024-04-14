#ifndef	CPPTABLE_H__
#define CPPTABLE_H__

#include <cstdint>
#include <memory>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <ctime>
#include <string>

#include "Define_CPPTable.h"

// 주의, 32비트로 만들고 64비트 호환모드로 사용하면 메모리가 절삭될 수 있습니다.
// 반드시 타겟 아키텍처를 일치시켜서 사용하세요.
#if _WIN64
using INTPTR = uint64_t;
#elif _WIN32
using INTPTR = uint32_t;
#endif

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

using eStr_t		= std::string;
using eInt_t		= int64_t;
using eFloat_t		= double;
using eDateTime_t	= __time64_t;

enum ERTTI
{
	ERTTI_UNKNOWN,
	ERTTI_DATETIME,
	ERTTI_INT,
	ERTTI_FLOAT,
	ERTTI_STR,
	ERTTI_MAX
};

// 동적 사이즈를 사용하는 문자열 관련 처리는 EMemory에서 대부분 처리하기
// 자신의 타입정보를 기록하고 반환할 때는 m_type대로 처리해서 돌려줍니다.
// 데이터 자체는 링크드 리스트로 관리하고,
// 테이블에서의 데이터 위치는 키값으로 처리합니다.
struct CPPTABLE_API EListValue
{
	ERTTI m_type = ERTTI::ERTTI_UNKNOWN;
	columnId_t m_column = 0;
	primaryId_t m_row = 0;
	EListValue* m_prev = nullptr;
	EListValue* m_next = nullptr;
	void* m_ptr = nullptr;
};

#include "IMemoryBlock.h"
#include "EMemoryBlock.h"
#include "EStaticMemoryBlock.h"
#include "EMemoryPool.h"
#include "EAllocator.h"

#include "ESchema.h"
#include "ERow.h"
#include "ETable.h"

#endif