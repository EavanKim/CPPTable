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

}