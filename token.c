#include "lexer.h" // header

#include <stdio.h> // putchar

#include "utilities/string.h" // String_*

void Token_create(Token *this)
{
	String_create(&this->data);
}

void Token_deinit(Token *this) {
	String_deinit(&this->data);
}

void Token_print(const Token *token)
{
	switch (token->kind)
	{
	case Token_Kind_ident:
		printf("ident %.*s", token->data.length, token->data.array);
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
		printf("intlt %.*s", token->data.length, token->data.array);
		break;
	case Token_Kind_strlt:
		printf("strlt %.*s", token->data.length, token->data.array);
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
	}

	putchar('\n');
}

bool Token_eq(const Token *this, const Token *token)
{
	if (this->kind != token->kind)
		return false;

	// handle cases with data

	switch (token->kind)
	{
	case Token_Kind_ident:
	case Token_Kind_intlt:
	case Token_Kind_strlt:
		if (!String_eq(&this->data, &token->data))
			return false;
	}

	return true;
}
