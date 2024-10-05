#include "string.h" // header guard

void String_init  (String *string)
{
	Vector_char_init  (string);
}

void String_deinit(String *string)
{
	Vector_char_deinit(string);
}

bool String_resize(String *string)
{
	Vector_char_resize(string);
}

bool String_append(String *string, char item)
{
	return Vector_char_append(string, item);
}

bool String_eq(const String *string_l, const char *string_r)
{
	if (string_l->length != strlen(string_r))
		return false;

	for (size_t i = 0; i < string_l->length; i++)
		if (string_l->array[i] != string_r[i])
			return false;

	return true;
}
