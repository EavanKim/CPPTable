#ifndef	DEFINE_CPPTABLE_H__
#define DEFINE_CPPTABLE_H__

#ifdef CPPTABLE_EXPORTS
#define CPPTABLE_API __declspec(dllexport)
#else
#define CPPTABLE_API __declspec(dllimport)
#endif

#endif