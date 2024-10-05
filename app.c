// TODO: investigate using C23 nullptr instead of NULL across all files

#include <ctype.h>  // tolower
#include <errno.h>  // errno
#include <stdio.h>  // FILE fopen fclose
#include <locale.h> // NULL
#include <stdlib.h> // EXIT_SUCCESS EXIT_FAILURE
#include <string.h> // strerror

#include "error.h"  // errorf
#include "lexer.h"  // tokenize

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

	Vector_Token tokens;
	Vector_Token_init  (&tokens);

	tokenize(&tokens, file);

	Vector_Token_deinit(&tokens);

	if (fclose(file))
	{
		const char *desc = strerror(errno);
		errorf("failure closing source file\n[%c%s]", tolower(desc[0]), &desc[1]);

		return EXIT_FAILURE;
	}

	printf("\nSuccess!\n");

	return EXIT_SUCCESS;
}
