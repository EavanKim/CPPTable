#include <iostream>
#include "CPPTable.h"
#include <Windows.h>

#define TESTCOUNT 10

void PrintMemoryByte(memSize_t _index, memSize_t _xLength, EBYTE _value)
{
	printf("\033[%d;%dH", ((_index / _xLength) + 4), (((_index % _xLength)) * 2));
	printf("%02x", _value);
	fflush(stdout);
}

int main()
{
	std::cout << "Hello World!\n";

	CPPTable::ETable table;
	EMemoryBlock test(8, TESTCOUNT, 16);
	std::vector<void*> ptrs;
	ptrs.reserve(TESTCOUNT);

	test.PrintDebugMemoryInfo(PrintMemoryByte);

	for (int seek = 0; TESTCOUNT > seek; ++seek)
	{
		int* ptr = (int*)test.EMalloc();
		if (nullptr != ptr)
		{
			*ptr = seek;
			ptrs.push_back(ptr);
			test.PrintDebugMemoryInfo(PrintMemoryByte);
		}
	}


	for (int seek = 0; TESTCOUNT > seek; ++seek)
	{
		test.EFree(ptrs[seek]);
		test.PrintDebugMemoryInfo(PrintMemoryByte);
	}

	ptrs.clear();
}