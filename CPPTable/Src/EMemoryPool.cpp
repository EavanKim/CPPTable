#include "../inc/CPPTable.h"

EMemoryPool::EMemoryPool(memSize_t _slackSize, memIndex_t _count)
	: m_slack(_slackSize)
	, m_count(_count)
	, m_blockSize(_slackSize + sizeof(EMemHeader))
	, m_poolSize((_slackSize + sizeof(EMemHeader))* _count)
{
	m_memory = new char[m_poolSize];

	EMemHeader* prev = nullptr;
	INTPTR currentMem = ParsePtr(m_memory);
	INTPTR maxMemRange = currentMem + m_poolSize;
	for (; m_poolSize > currentMem; currentMem += m_blockSize)
	{
		EMemHeader* header = (EMemHeader*)ParsePtr(currentMem);
		header->m_prev = prev;
		if (nullptr != prev)
			prev->m_next = header;

		prev = header;
	}
}

EMemoryPool::~EMemoryPool()
{
	if (nullptr != m_memory)
		delete[] m_memory;

	m_memory = nullptr;
}

void* EMemoryPool::EMalloc()
{
	void* result = nullptr;

	if (nullptr != m_free)
	{
		INTPTR target = ParsePtr(m_free);
		result = ParsePtr(target + headerSize);
		m_free = m_free->m_next;
	}

	return result;
}

bool EMemoryPool::EFree(void* _free)
{
	// 어차피 template 타입별 static 값이 될 것이므로 안심하고 쓰기
	INTPTR target = ParsePtr(_free);
	INTPTR start = ParsePtr((void*)m_memory);

	INTPTR seek = start - target;
	if (-1 < seek) // 0보다 작다면, 메모리 영역 할당보다 앞쪽 메모리
	{
		if (m_poolSize > seek) // last보다 크다면 할당 범위 바깥쪽이므로 풀 보다 더 뒤쪽 메모리
		{
			EMemHeader* header = (EMemHeader*)ParsePtr(target - headerSize);
			header->SetNext(m_free);
			m_free = header;

			return true;
		}
	}

	return false;
}