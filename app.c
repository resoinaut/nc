// TODO: investigate using C23 nullptr instead of NULL across all files
// TODO: investigate using C99 restrict where applicable across all files

#include <ctype.h>  // tolower
#include <errno.h>  // errno
#include <stdio.h>  // FILE fopen fclose
#include <locale.h> // NULL
#include <stdlib.h> // EXIT_SUCCESS EXIT_FAILURE
#include <string.h> // strerror

#include "lexer.h"  // tokenize
#include "error.h"  // errorf
#include "shell.h"  // shellf Vector_int_* Shell_Mark_*

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 2)
	{
		Vector_int indices;
		Vector_int_create(&indices);
		Vector_int_append(&indices, 0);

		errorf("expected 1 argument and received %i", argc - 1);
		shellf(argc, argv, &indices, Shell_Mark_other_indices);

		Vector_int_deinit(&indices);

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
	Vector_Token_create(&tokens);

	if (tokenize(&tokens, file))
	{
		Vector_Token_deinit(&tokens);
		return EXIT_FAILURE;
	}

	// temporary

	putchar('\n');

	for (size_t i = 0; i < tokens.length; i++)
		Token_print(&tokens.array[i]);

	// end

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
