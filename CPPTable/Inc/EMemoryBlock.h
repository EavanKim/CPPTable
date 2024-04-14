#ifndef	EMEMORYBLOCK_H__
#define EMEMORYBLOCK_H__

/// <summary>
/// 하나의 메모리 관리 chunk입니다.
/// </summary>
/// <typeparam name="staticSize"></typeparam>

class CPPTABLE_API EMemoryBlock : public IMemoryBlock
{
public:
	EMemoryBlock(const memSize_t _segmentSize, const memSize_t _blockSize, const memSize_t _allignedByte)
		: staticBlockSize(_blockSize)
		, segmentSize(_segmentSize)
		, headerSize(sizeof(MemoryHeader))
		, tailSize(sizeof(MemoryTail))
		, totalSegmentInfoDataSize(sizeof(MemoryHeader) + sizeof(MemoryTail))
		, totalManageDataSize(sizeof(MemoryHeader) + sizeof(MemoryTail) + _segmentSize)
		, paddingSize( (_allignedByte - ((sizeof(MemoryHeader) + sizeof(MemoryTail) + _segmentSize ) % _allignedByte)) % (~_allignedByte))
	{
		m_data = new EBYTE[_blockSize];
		memset(m_data, 0, _blockSize);
		m_start = ParsePtr(m_data);
		m_end = m_start + _blockSize;

		INTPTR memSeek = m_start;

		do
		{
			INTPTR prevStart = memSeek;
			MemoryHeader* prevHeader = (MemoryHeader*)ParsePtr(prevStart);
			memSeek += totalManageDataSize + paddingSize;
			MemoryHeader* nextHeader = (MemoryHeader*)ParsePtr(memSeek);

			prevHeader->next_ = nextHeader;
			m_free.insert(ParsePtr((prevStart + headerSize)));
			if (m_end > memSeek)
			{
				nextHeader->prev_ = prevHeader;
			}
		} while (m_end > memSeek);
	}

	~EMemoryBlock()
	{
		if (nullptr != m_data)
		{
			delete[] m_data;
			m_data = nullptr;
		}
	}

	virtual void* Malloc(memSize_t _size)
	{
		void* result = nullptr;
		if (m_free.size())
		{
			result = *m_free.begin();
			m_free.erase(result);
		}

		return result;
	}

	virtual void Free(void* _ptr)
	{
		if (CheckRange(_ptr))
		{
			m_free.insert(_ptr);
		}
		else
		{
			throw std::exception("Need Range Check!!!");
		}
	}

	virtual bool CheckRange(void* _ptr)
	{
		INTPTR checkTarget = ParsePtr(_ptr);
		if (m_start <= checkTarget)
		{
			if (m_end > checkTarget) // 끝과 같으면 Chunk Memory 관련 Memory Overrun 이 발생했습니다. 실패로 던집니다.
			{
				return true;
			}
		}

		return false;
	}

private:
	const memSize_t staticBlockSize = 0;
	const memSize_t segmentSize = 0;
	const memSize_t headerSize = 0;
	const memSize_t tailSize = 0;
	const memSize_t paddingSize = 0;
	const memSize_t totalManageDataSize = 0;
	const memSize_t totalSegmentInfoDataSize = 0;
	INTPTR m_start = 0;
	INTPTR m_end = 0;
	std::unordered_set<void*> m_free;
	EBYTE* m_data = nullptr;
};

#endif