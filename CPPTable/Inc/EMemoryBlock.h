#ifndef	EMEMORYBLOCK_H__
#define EMEMORYBLOCK_H__

#include <fstream>
#include <cassert>

struct memHeader
{
	bool free_;
};

/// <summary>
/// 하나의 메모리 관리 chunk입니다.
/// </summary>
/// <typeparam name="staticSize"></typeparam>

class CPPTABLE_API EMemoryBlock
{
public:
	EMemoryBlock(const memSize_t _segmentSize, const memSize_t _count = 10, const memSize_t _allignedByte = 16)
		: blockCount(_count)
		, segmentSize(_segmentSize)
		, headerSize(sizeof(memHeader))
		, paddingSize((_allignedByte - ((sizeof(memHeader) + _segmentSize) % _allignedByte)) % (~_allignedByte))
		, totalManageDataSize(sizeof(memHeader) + _segmentSize + ((_allignedByte - ((sizeof(memHeader) + _segmentSize) % _allignedByte)) % (~_allignedByte)))
		, totalMemorySize((sizeof(memHeader) + _segmentSize + ((_allignedByte - ((sizeof(memHeader) + _segmentSize) % _allignedByte)) % (~_allignedByte))) * _count)
	{
		m_data = new EBYTE[totalMemorySize];
		memset(m_data, 0x00, totalMemorySize);
		m_start = ParsePtr(m_data);
		m_end = m_start + totalMemorySize;

		INTPTR seek = m_start;

		while (m_end > seek)
		{
			memHeader* header = (memHeader*)ParsePtr(seek);
			header->free_ = true;
			seek += totalManageDataSize;
		}
	}

	~EMemoryBlock()
	{
		if (nullptr != m_data)
		{
			delete[] m_data;
			m_data = nullptr;
		}
	}

	virtual void* EMalloc()
	{
		INTPTR start = m_start;
		while (m_end > start)
		{
			memHeader* header = (memHeader*)ParsePtr(start);
			if (header->free_)
			{
				header->free_ = false;
				return  ParsePtr(start + headerSize);
			}

			start += totalManageDataSize;
		}

		return nullptr;
	}

	virtual void EFree(void* _ptr)
	{
		if (CheckRange(_ptr))
		{
			memHeader* header = (memHeader*)ParsePtr(ParsePtr(_ptr) + headerSize);
			header->free_ = true;
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

	virtual void PrintDebugMemoryInfo(void(*_func)(memSize_t, memSize_t, EBYTE))
	{
		if (nullptr != _func)
		{
			for (memSize_t seek = 0; totalMemorySize > seek; ++seek)
				_func(seek, totalManageDataSize, m_data[seek]);
		}
	}

	const memSize_t totalMemorySize = 0;
	const memSize_t blockCount = 0;
	const memSize_t segmentSize = 0;
	const memSize_t headerSize = 0;
	const memSize_t paddingSize = 0;
	const memSize_t totalManageDataSize = 0;
private:
	INTPTR m_start = 0;
	INTPTR m_end = 0;
	EBYTE* m_data = nullptr;
};

#endif