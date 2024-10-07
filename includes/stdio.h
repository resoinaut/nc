#pragma once

#ifndef _STDIO_H
#define _STDIO_H

#include "__null.h"
#include "__size_t.h"
#include "__version.h"

#include "stddef.h"
#include "string.h"
#include "windows.h"

// format: const char *         until C99
// format: const char *restrict since C99

#define __restrict

#ifdef  __C99
#define __restrict restrict
#endif

int printf(const char *__restrict format, ...)
{
	// TODO: implement formatting and varargs
	// TODO: look into moving GetStdHandle into the global scope

	DWORD  count;

	HANDLE handle  = GetStdHandle(STD_OUTPUT_HANDLE);
	BOOL   success = WriteConsoleA(handle, format, strlen(format), &count, NULL);

	return success ? count : -1;
}

#endif // header guard
