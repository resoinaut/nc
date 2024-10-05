#include <stdio.h>  // putc fprintf vfprintf stderr
#include <stdarg.h> // va_list va_start va_end

void errorf(const char *error, ...)
{
	#define red     "\x1b[31m"
	#define default "\x1b[39m"

	va_list  args;
	va_start(args, error);

	fprintf (stderr, "\n" red "error:" default " ");
	vfprintf(stderr, error, args);
	putc    ('\n', stderr);

	va_end(args);

	#undef  red
	#undef  default
}
