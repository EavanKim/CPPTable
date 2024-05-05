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
	IEntity m_;

	m_ = (eInt_t)100;
	m_ = 99.f;
	m_ = (eDateTime_t)999;
	m_ = "1000000000000000";

	FILE* fPtr = nullptr;
	fopen_s(&fPtr, "./table.t", "w+");
	if (nullptr != fPtr)
	{
		m_.Save(fPtr);
		m_.Load(fPtr);
		fclose(fPtr);
	}
}