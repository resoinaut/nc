#pragma once

#include <stdio.h>   // FILE
#include <stdbool.h> // bool

#include "utilities/string.h" // String
#include "utilities/vector.h" // DECLARE_VECTOR_OF

typedef struct
{
	enum Token_Kind
	{
		Token_Kind_ident, // contains data

		// keywords

		Token_Kind_keywd_int,
		Token_Kind_keywd_void,
		Token_Kind_keywd_return,

		// literals

		Token_Kind_intlt, // contains data
		Token_Kind_strlt, // contains data

		// delimiters

		Token_Kind_curly_opened,
		Token_Kind_curly_closed,

		Token_Kind_paren_opened,
		Token_Kind_paren_closed,

		Token_Kind_semic,
	} kind;

	String data;
} Token;

DECLARE_VECTOR_OF(Token)

bool tokenize(Vector_Token *tokens, FILE *file);
