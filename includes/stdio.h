#pragma once

#ifndef _STDIO_H
#define _STDIO_H

#include "__size_t.h"
#include "__version.h"

#include "stddef.h"
#include "string.h"
#include "windows.h"

#define __restrict

#ifdef  __C99
#define __restrict restrict
#endif

// format: const char *         until C99
// format: const char *restrict since C99

int printf(const char *__restrict format, ...)
{
	// TODO: implement formatting and varargs
	// TODO: look into moving GetStdHandle into the global scope

	HANDLE handle  = GetStdHandle(STD_OUTPUT_HANDLE);
	BOOL   success = WriteConsoleA(handle, format, strlen(format), NULL, NULL);

	if (!success) return -1;
}

#endif // header guard
