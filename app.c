#include <stdio.h>        // FILE fopen fclose tmpfile
#include <locale.h>       // NULL
#include <stdlib.h>       // EXIT_SUCCESS EXIT_FAILURE
#include <stdbool.h>      // bool true false

#include "error.h"        // errorf errnof
#include "shell.h"        // shellf Vector_int_* Shell_Mark_*
#include "lexer.h"        // tokenize
#include "preprocessor.h" // preprocess

#include "errormessage.h" // failure_opening_src_file
                          // failure_closing_src_file
						  // failure_getting_tmp_file
						  // failure_closing_tmp_file

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 2)
	{
		errorf("expected 1 argument and received %i", argc - 1);
		shellf(argc, argv, Shell_Mark_other_indices, 1, 0);

		return EXIT_FAILURE;
	}

	FILE *src_file = fopen(argv[1], "r");

	if (src_file == NULL)
	{
		errnof(failure_opening_src_file);
		shellf(argc, argv, Shell_Mark_given_indices, 1, 1);

		return EXIT_FAILURE;
	}

	// driver

	int   failure;
	FILE *tmp_file = tmpfile();

	if (tmp_file == NULL)
	{
		errnof(failure_getting_tmp_file);

		if (fclose(src_file))
		{
			errnof(failure_closing_src_file);
			shellf(argc, argv, Shell_Mark_given_indices, 1, 1);
		}

		return EXIT_FAILURE;
	}

	// preprocessor

	failure = preprocess(tmp_file, src_file, argv[1]);

	if (fclose(src_file))
	{
		errnof(failure_closing_src_file);
		shellf(argc, argv, Shell_Mark_given_indices, 1, 1);

		if (fclose(tmp_file))
			errnof(failure_closing_tmp_file);

		return EXIT_FAILURE;
	}

	if (failure)
	{
		if (fclose(tmp_file))
			errnof(failure_closing_tmp_file);

		return EXIT_FAILURE;
	}

	printf("\n------\n");
	int ch;
	while ((ch = getc(tmp_file)) != EOF)
		putchar(ch);
	rewind(tmp_file);
	printf("\n------");

	// tokenization

	Vector_Token tokens;
	Vector_Token_create(&tokens);

	failure = tokenize(&tokens, tmp_file);

	if (fclose(tmp_file))
	{
		Vector_Token_deinit(&tokens);
		errnof(failure_closing_tmp_file);
		return EXIT_FAILURE;
	}

	if (failure)
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

	printf("\nSuccess!\n");

	return EXIT_SUCCESS;
}
