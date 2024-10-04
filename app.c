#include <ctype.h>  // tolower
#include <errno.h>  // errno
#include <stdio.h>  // FILE putc fopen fclose fprintf stderr
#include <stdarg.h> // va_list va_start va_end
#include <stdlib.h> // EXIT_SUCCESS EXIT_FAILURE
#include <string.h> // strerror

void errorf(const char *error, ...)
{
	va_list  args;
	va_start(args, error);

	fprintf (stderr, "\n\x1b[31merror:\x1b[39m ");
	vfprintf(stderr, error, args);
	putc    ('\n', stderr);

	va_end(args);
}

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 2)
	{
		errorf("expected 1 argument and received %i", argc - 1);

		return EXIT_FAILURE;
	}

	const char *filename = argv[1];

	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		const char *desc = strerror(errno);
		errorf("failure opening source file: %c%s", tolower(desc[0]), &desc[1]);

		return EXIT_FAILURE;
	}

	printf("Success!");
	fclose(file);

	return EXIT_SUCCESS;
}
