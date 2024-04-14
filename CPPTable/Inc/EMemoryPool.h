#ifndef	EMEMORYPOOL_H__
#define EMEMORYPOOL_H__

struct CPPTABLE_API EMemHeader
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

class CPPTABLE_API EMemoryPool
{
public:
	EMemoryPool(memSize_t _slackSize, memIndex_t _count);
	~EMemoryPool();

	void* EMalloc();
	bool EFree(void* _free);

	static const memSize_t headerSize = sizeof(EMemHeader);
	const memSize_t m_slack = 0;
	const memIndex_t m_count = 0;
	const memSize_t m_blockSize = 0;
	const memSize_t m_poolSize = 0;
	EMemHeader* m_free = nullptr;
	void* m_memory = nullptr;
};

#endif