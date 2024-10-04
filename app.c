#include <ctype.h>  // tolower
#include <errno.h>  // errno
#include <stdio.h>  // FILE putc fopen fclose fprintf stderr
#include <stdarg.h> // va_list va_start va_end
#include <stdlib.h> // EXIT_SUCCESS EXIT_FAILURE
#include <string.h> // strerror

void errorf(const char *error, ...)
{
	#define RED     "\x1b[31m"
	#define DEFAULT "\x1b[39m"

	va_list  args;
	va_start(args, error);

	fprintf (stderr, "\n" RED "error:" DEFAULT " ");
	vfprintf(stderr, error, args);
	putc    ('\n', stderr);

	va_end(args);

	#undef RED
	#undef DEFAULT
}

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 2)
	{
		errorf("expected 1 argument and received %i", argc - 1);
		return EXIT_FAILURE;
	}

	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		const char *desc = strerror(errno);
		errorf("failure opening source file\n[%c%s]", tolower(desc[0]), &desc[1]);

		return EXIT_FAILURE;
	}

	// ...

	if (fclose(file))
	{
		const char *desc = strerror(errno);
		errorf("failure closing source file\n[%c%s]", tolower(desc[0]), &desc[1]);

		return EXIT_FAILURE;
	}

	printf("\nSuccess!\n");

	return EXIT_SUCCESS;
}
