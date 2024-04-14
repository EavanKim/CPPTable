#ifndef ESTATICMEMORYBLOCK_H__
#define ESTATICMEMORYBLOCK_H__

class CPPTABLE_API EStaticMemoryBlock : public IMemoryBlock
{
public:
	EStaticMemoryBlock(const memSize_t _memSize)
		: staticBlockSize(_memSize)
	{
		memset(m_data, 0, staticBlockSize);
		m_start = ParsePtr(m_data);
		m_end = m_start + staticBlockSize;
	}

	~EStaticMemoryBlock()
	{

	}

	virtual void* Malloc(memSize_t _size)
	{
		return nullptr;
	}

	virtual void Free(void* _ptr)
	{
		
	}

	virtual bool CheckRange(void*)
	{
		return false;
	}

private:
	const memSize_t staticBlockSize = 0;
	INTPTR m_start = 0;
	INTPTR m_end = 0;
	std::unordered_set<EBYTE*> m_free;
	std::unordered_set<EBYTE*> m_used;
	EBYTE* m_data = nullptr;
};

#endif