#pragma once

#include <stdarg.h> // va_list

void verrorf(const char *error, va_list args);

void errorf(const char *error, ...);
void errnof(const char *error, ...);
