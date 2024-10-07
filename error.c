#include "error.h" // header guard

#include <ctype.h>  // tolower
#include <errno.h>  // errno
#include <stdio.h>  // putc fprintf vfprintf stderr
#include <stdarg.h> // va_list va_start va_end
#include <string.h> // strcmp strerror

void verrorf(const char *error, va_list args)
{
	#define RED     "\x1b[31m"
	#define DEFAULT "\x1b[39m"

	fprintf (stderr, "\n" RED "error:" DEFAULT " ");
	vfprintf(stderr, error, args);
	putc    ('\n', stderr);

	#undef  RED
	#undef  DEFAULT
}

void errorf(const char *error, ...)
{
	va_list  args;
	va_start(args, error);

	verrorf(error, args);

	va_end(args);
}

void errnof(const char *error, ...)
{
	va_list  args;
	va_start(args, error);

	verrorf(error, args);

	const char *err = strerror(errno);

	if (strcmp(err, strerror(0)) != 0)
		fprintf(stderr, "[%c%s]\n", tolower(err[0]), &err[1]);

	va_end(args);
}
