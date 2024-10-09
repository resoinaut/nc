#include "lexer.h"            // header

#include <ctype.h>            // isspace isalpha isalnum isdigit
#include <stdio.h>            // FILE getc ungetc

#include "error.h"            // errnof
#include "errormessage.h"     // failure_reading_tmp_file

#include "utilities/string.h" // String_*

void _lexer_handle_failure_reading_tmp_file()
{
	errnof(failure_reading_tmp_file);
}

// returns 0 on success and 1 on failure
int tokenize(Vector_Token *tokens, FILE *file)
{
	#define APPEND_TOKEN();                     \
		if (Vector_Token_append(tokens, token)) \
			return 1                            \

	int ch;

	size_t row = 1;
	size_t col = 1;

	while ((ch = getc(file)) != EOF)
	{
		if (ch == '\n')
		{
			row++;
			col = 1;
		}
		else col++;

		if (isspace(ch))
			continue;

		Token token;
		Token_create(&token);

		// handle symbols

		switch (ch)
		{
		// literals

		case '"':
			while ((ch = getc(file)) != EOF)
				if (ch == '"') break;
				else if (String_append(&token.data, ch))
					return 1;

			if (ferror(file))
			{
				Token_deinit(&token);
				_lexer_handle_failure_reading_tmp_file();
				return 1;
			};

			if (feof(file))
			{
				errorf("unterminated string literal");
				return 1;
			}

			// broke out of loop

			token.kind = Token_Kind_strlt;
			APPEND_TOKEN();
			continue;

		// delimiters

		case ';':
			token.kind = Token_Kind_semic;
			APPEND_TOKEN();
			continue;

		case '{':
			token.kind = Token_Kind_curly_opened;
			APPEND_TOKEN();
			continue;

		case '}':
			token.kind = Token_Kind_curly_closed;
			APPEND_TOKEN();
			continue;

		case '(':
			token.kind = Token_Kind_paren_opened;
			APPEND_TOKEN();
			continue;

		case ')':
			token.kind = Token_Kind_paren_closed;
			APPEND_TOKEN();
			continue;
		}

		// handle identifiers

		if (isalpha(ch) || ch == '_')
		{
			if (String_append(&token.data, ch))
				return 1;

			while ((ch = getc(file)) != EOF)
			{
				if (!isalnum(ch) && ch != '_')
				{
					ungetc(ch, file);
					break;
				}

				if (String_append(&token.data, ch))
					return 1;
			}

			// handle keywords

			if (ferror(file))
			{
				Token_deinit(&token);
				_lexer_handle_failure_reading_tmp_file();
				return 1;
			}

			if      (String_eq_cstr(&token.data, "int"))
				token.kind = Token_Kind_keywd_int;
			else if (String_eq_cstr(&token.data, "void"))
				token.kind = Token_Kind_keywd_void;
			else if (String_eq_cstr(&token.data, "return"))
				token.kind = Token_Kind_keywd_return;
			else
				token.kind = Token_Kind_ident;

			APPEND_TOKEN();

			continue;
		}

		// handle int literals

		if (isdigit(ch))
		{
			if (String_append(&token.data, ch))
				return 1;

			while ((ch = getc(file)) != EOF)
			{
				if (!isdigit(ch))
				{
					ungetc(ch, file);
					break;
				}

				if (String_append(&token.data, ch))
					return 1;
			}

			if (ferror(file))
			{
				Token_deinit(&token);
				_lexer_handle_failure_reading_tmp_file();
				return 1;
			}

			token.kind = Token_Kind_intlt;
			APPEND_TOKEN();

			continue;
		}

		// invalid character

		Token_deinit(&token);

		errorf("invalid character '%c' at %zu:%zu", ch, row, col);

		return 1;
	}

	if (ferror(file))
	{
		_lexer_handle_failure_reading_tmp_file();
		return 1;
	}

	// EOF

	return 0;

	#undef APPEND_TOKEN
}
