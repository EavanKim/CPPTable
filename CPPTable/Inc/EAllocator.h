#ifndef	IEALLOC_H__
#define IEALLOC_H__

class CPPTABLE_API EAllocator
{
public:

private:


	EListValue* m_free = nullptr;
	EListValue* m_used = nullptr;

	EBYTE* m_data = nullptr;
};

#endif