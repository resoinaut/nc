#include "lexer.h"            // header

#include <ctype.h>            // isalpha isalnum
#include <errno.h>            // errno
#include <stdio.h>            // EOF FILE getc
#include <string.h>           // strerror strcmp
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
	#define APPEND_TOKEN                        \
		if (Vector_Token_append(tokens, token)) \
			return true;                        \

	int ch;

	while ((ch = getc(file)) != EOF)
	{
		if (isspace(ch))
			continue;

		Token token;
		Token_init(&token);

		// handle symbols

		switch (ch)
		{
		// literals

		case '"':
			while ((ch = getc(file)) != EOF)
				if (ch == '"') break;
				else if (String_append(&token.data, ch))
					return true;

			if (ferror(file)) goto handle_ferror;

			if (feof(file))
			{
				errorf("unterminated string literal");
				return true;
			}

			// broke out of loop

			token.kind = Token_Kind_strlt;
			APPEND_TOKEN
			continue;

		// delimiters

		case ';':
			token.kind = Token_Kind_semic;
			APPEND_TOKEN
			continue;

		case '{':
			token.kind = Token_Kind_curly_opened;
			APPEND_TOKEN
			continue;

		case '}':
			token.kind = Token_Kind_curly_closed;
			APPEND_TOKEN
			continue;

		case '(':
			token.kind = Token_Kind_paren_opened;
			APPEND_TOKEN
			continue;

		case ')':
			token.kind = Token_Kind_paren_closed;
			APPEND_TOKEN
			continue;
		}

		// handle identifiers

		if (isalpha(ch) || ch == '_')
		{
			if (String_append(&token.data, ch))
				return true;

			while ((ch = getc(file)) != EOF)
			{
				if (!isalnum(ch) && ch != '_')
				{
					ungetc(ch, file);
					break;
				}

				if (String_append(&token.data, ch))
					return true;
			}

			// handle keywords

			if (ferror(file)) goto handle_ferror;

			if      (String_eq(&token.data, "int"))
				token.kind = Token_Kind_keywd_int;
			else if (String_eq(&token.data, "void"))
				token.kind = Token_Kind_keywd_void;
			else if (String_eq(&token.data, "return"))
				token.kind = Token_Kind_keywd_return;
			else
				token.kind = Token_Kind_ident;

			APPEND_TOKEN

			continue;
		}

		// handle int literals

		if (isdigit(ch))
		{
			if (String_append(&token.data, ch))
				return true;

			while ((ch = getc(file)) != EOF)
			{
				if (!isdigit(ch))
				{
					ungetc(ch, file);
					break;
				}

				if (String_append(&token.data, ch))
					return true;
			}

			if (ferror(file)) goto handle_ferror;

			token.kind = Token_Kind_intlt;
			APPEND_TOKEN

			continue;
		}

		// invalid character

		errorf("invalid character '%c'", ch);

		return true;
	}

	if (ferror(file))
	{
		handle_ferror:

		const char *desc = strerror(errno);
		errorf("failure reading source file\n[%c%s]", tolower(desc[0]), &desc[1]);

		return true;
	}

	// EOF

	return false;

	#undef APPEND_TOKEN
}
