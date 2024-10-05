#include "lexer.h"            // header

#include <ctype.h>            // isalpha isalnum
#include <errno.h>            // errno
#include <stdio.h>            // EOF FILE getc
#include <string.h>           // strerror
#include <stdbool.h>          // bool true false

#include "error.h"            // errorf
#include "utilities/string.h" // String String_init String_deinit

void Token_init  (Token *token)
{
	String_init  (&token->data);
}

void Token_deinit(Token *token)
{
	String_deinit(&token->data);
}

bool tokenize(Vector_Token *tokens, FILE *file)
{
	return false; // temporary; to prevent errors

	int ch;

	while ((ch = getc(file)) != EOF)
	{
		// handle identifiers

		if (isalpha(ch) || ch == '_')
		{
			Token token;
		}

		// handle int literals

		if (isdigit(ch))
		{}

		// handle str literals

		// ...
	}

	if (ferror(file))
	{
		const char *desc = strerror(errno);
		errorf("failure reading source file\n[%c%s]", tolower(desc[0]), &desc[1]);

		return true;
	}

	// EOF

	return false;
}
