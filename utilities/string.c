#include "string.h" // header guard

void String_init  (String *this)
{
	Vector_char_init  (this);
}

void String_deinit(String *this)
{
	Vector_char_deinit(this);
}

bool String_resize(String *this)
{
	Vector_char_resize(this);
}

bool String_append(String *this, char ch)
{
	return Vector_char_append(this, ch);
}

bool String_has(const String *this, char ch)
{
	return Vector_char_has(this, ch);
}

bool String_eq(const String *this, const String *string)
{
	return Vector_char_eq(this, string);
}

bool String_eq_cstr(const String *this, const char *cstr)
{
	if (this->length != strlen(cstr))
		return false;

	for (size_t i = 0; i < this->length; i++)
		if (this->array[i] != cstr[i])
			return false;

	return true;
}
