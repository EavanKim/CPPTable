#ifndef	IMEMORYBLOCK_H__
#define IMEMORYBLOCK_H__

struct CPPTABLE_API MemoryHeader
{
	MemoryHeader* prev_;
	MemoryHeader* next_;
};

struct CPPTABLE_API MemoryTail
{
	uint32_t data_ = 0x12345678; // Sanity Check용 데이터.
};

class CPPTABLE_API IMemoryBlock
{
public:
	virtual void* Malloc(memSize_t _size) = 0;
	virtual void Free(void* _free) = 0;
	virtual bool CheckRange(void*) = 0;
};

#endif