// TODO: move GetStdHandle to global scope
// TODO: implement strlen and NULL
// TODO: finish printf implementation

#pragma once

#ifndef _STDIO_H
#define _STDIO_H

#include "__utilities.h"

#include "windows.h"

// format: const char *         until C99
// format: const char *restrict since C99

int printf(const char *__restrict format, ...)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	WriteConsoleA(handle, format, strlen(format), NULL, NULL);
}

#endif // header guard
