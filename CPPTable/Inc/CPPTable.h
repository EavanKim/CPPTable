#ifndef	CPPTABLE_H__
#define CPPTABLE_H__

#include <cstdint>

#if _WIN32
using INTPTR = uint32_t;
#elif _WIN64
using INTPTR = uint64_t;
#endif

typedef unsigned long memSize_t;
typedef unsigned long memIndex_t;

// 동적 사이즈를 사용하는 문자열 관련 처리는 EMemory에서 대부분 처리하기
struct EMemory
{
	memSize_t m_size = 0;
	EMemory* m_prev = nullptr;
	EMemory* m_next = nullptr;
	void* m_ptr = nullptr;
};

#include "Define_CPPTable.h"

#include "EMemoryPool.h"
#include "EAlloc.h"

#include "ESchema.h"
#include "ERow.h"
#include "ETable.h"

#endif