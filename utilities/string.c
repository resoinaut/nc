#include "string.h" // header guard

bool String_eq_cstr(const String *this, const char *cstr)
{
	if (this->length != strlen(cstr))
		return false;

	for (size_t i = 0; i < this->length; i++)
		if (this->array[i] != cstr[i])
			return false;

	return true;
}
