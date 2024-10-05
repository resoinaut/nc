// TODO: investigate using C23 nullptr instead of NULL across all files
// TODO: investigate using C99 restrict where applicable across all files

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

	if (tokenize(&tokens, file))
	{
		Vector_Token_deinit(&tokens);
		return EXIT_FAILURE;
	}

	// temporary

	for (size_t i = 0; i < tokens.length; i++)
	{
		Token token = tokens.array[i];

		putchar('\n');

		switch (token.kind)
		{
		case Token_Kind_ident:
			printf("ident %.*s", token.data.length, token.data.array);
			break;
		case Token_Kind_keywd_int:
			printf("keywd int");
			break;
		case Token_Kind_keywd_void:
			printf("keywd void");
			break;
		case Token_Kind_keywd_return:
			printf("keywd return");
			break;
		case Token_Kind_intlt:
			printf("intlt %.*s", token.data.length, token.data.array);
			break;
		case Token_Kind_strlt:
			printf("strlt %.*s", token.data.length, token.data.array);
			break;
		case Token_Kind_semic:
			printf("delim ;");
			break;
		case Token_Kind_curly_opened:
			printf("delim {");
			break;
		case Token_Kind_curly_closed:
			printf("delim }");
			break;
		case Token_Kind_paren_opened:
			printf("delim (");
			break;
		case Token_Kind_paren_closed:
			printf("delim )");
			break;
		default:
			printf("unrecognised token");
			break;
		}
	}

	putchar('\n');

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
