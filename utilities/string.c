#include "string.h"   // header guard

#include <locale.h>   // NULL
#include <stdlib.h>   // malloc

#include "../error.h" // errorf

char *slice_to_cstr(const Slice *slice)
{
	char *cstr = malloc(slice->length + 1);

	if (cstr == NULL)
	{
		errorf("failure allocating memory");
		return NULL;
	}

	for (size_t i = 0; i < slice->length; i++)
		cstr[i] = slice->array[i];

	cstr[slice->length] = '\0';

	return cstr;
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
