#ifndef	EMEMORYPOOL_H__
#define EMEMORYPOOL_H__

struct EMemHeader
{
	__forceinline void Clear()
	{
		if (m_prev && m_prev->m_next)
			m_prev->m_next = m_next;

		if (m_next && m_next->m_prev)
			m_next->m_prev = m_prev;

		m_prev = nullptr;
		m_next = nullptr;
	}

	__forceinline void SetPrev(EMemHeader* _prev)
	{
		if (m_prev && m_prev->m_next)
			m_prev->m_next = m_next;

		if (m_next && m_next->m_prev)
			m_next->m_prev = m_prev;

		m_prev = _prev;
		m_next = _prev->m_next;

		if (m_prev)
			m_prev->m_next = this;

		if (m_next)
			m_next->m_prev = this;
	}

	__forceinline void SetNext(EMemHeader* _next)
	{
		if (m_prev && m_prev->m_next)
			m_prev->m_next = m_next;

		if (m_next && m_next->m_prev)
			m_next->m_prev = m_prev;

		m_prev = _next->m_prev;
		m_next = _next;

		if (m_prev)
			m_prev->m_next = this;

		if (m_next)
			m_next->m_prev = this;
	}

#if _DEBUG // 디버그 값 설정하려면 쓰기
#endif
	EMemHeader* m_prev = nullptr;
	EMemHeader* m_next = nullptr;
};

template<typename T>
__forceinline INTPTR ParsePtr(T* _ptr)
{
	return (INTPTR)_ptr;
}

template<typename T>
__forceinline T* ParsePtr(INTPTR _int)
{
	return (T*)_int;
}

class EMemoryPool
{
public:
	EMemoryPool(memSize_t _slackSize, memIndex_t _count)
		: m_slack(_slackSize)
		, m_count(_count)
		, m_blockSize(_slackSize + sizeof(EMemHeader))
		, m_poolSize((_slackSize + sizeof(EMemHeader)) * _count)
	{
		EMemHeader* prev = nullptr;
		INTPTR currentMem = ParsePtr(m_memory);
		INTPTR maxMemRange = currentMem + m_poolSize;
		for (; m_poolSize > currentMem; currentMem += m_blockSize)
		{
			EMemHeader* header = ParsePtr<EMemHeader>(currentMem);
			header->m_prev = prev;
			if(nullptr != prev)
				prev->m_next = header;

			prev = header;
		}
	}

	~EMemoryPool()
	{
		if (nullptr != m_memory)
			delete[] m_memory;

		m_memory = nullptr;
	}

	template<typename T> T* EMalloc()
	{
		T* result = nullptr;

		if (nullptr != m_free)
		{
			INTPTR target = ParsePtr(m_free);
			result = ParsePtr<T>(target + headerSize);
			m_free = m_free->m_next;
		}

		return result;
	}

	bool EFree(void* _free)
	{
		// 어차피 template 타입별 static 값이 될 것이므로 안심하고 쓰기
		INTPTR target = ParsePtr(_free);
		INTPTR start = ParsePtr(m_memory);

		INTPTR seek = start - target;
		if (-1 < seek) // 0보다 작다면, 메모리 영역 할당보다 앞쪽 메모리
		{
			if (m_poolSize > seek) // last보다 크다면 할당 범위 바깥쪽이므로 풀 보다 더 뒤쪽 메모리
			{
				EMemHeader* header = ParsePtr<EMemHeader>(target - headerSize);
				header->SetNext(m_free);
				m_free = header;

				return true;
			}
		}

		return false;
	}

	static const memSize_t headerSize = sizeof(EMemHeader);
	const memSize_t m_slack = 0;
	const memIndex_t m_count = 0;
	const memSize_t m_blockSize = 0;
	const memSize_t m_poolSize = 0;
	EMemHeader* m_free = nullptr;
	const char* m_memory = nullptr;
};

#endif