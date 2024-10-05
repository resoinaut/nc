#pragma once

#include <stdio.h>            // FILE
#include <stdbool.h>          // bool

#include "utilities/string.h" // String
#include "utilities/vector.h" // DECLARE_VECTOR_OF

typedef enum
{
	Token_Kind_ident,         // contains data

	// keywords

	Token_Kind_keywd_int,
	Token_Kind_keywd_void,
	Token_Kind_keywd_return,

	// literals

	Token_Kind_intlt,         // contains data
	Token_Kind_strlt,         // contains data

	// delimiters

	Token_Kind_semic,         // ;

	Token_Kind_curly_opened,  // {
	Token_Kind_curly_closed,  // }

	Token_Kind_paren_opened,  // (
	Token_Kind_paren_closed,  // )
} Token_Kind;

typedef struct
{
	String     data;
	Token_Kind kind;
} Token;

void Token_init  (Token *token);
void Token_deinit(Token *token);

DECLARE_VECTOR_OF(Token)

bool tokenize(Vector_Token *tokens, FILE *file);
