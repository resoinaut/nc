#include "vector.h"   // header

#include <ctype.h>    // tolower
#include <errno.h>    // errno
#include <locale.h>   // NULL
#include <stddef.h>   // size_t
#include <stdlib.h>   // realloc free
#include <string.h>   // strerror
#include <stdbool.h>  // bool true false

#include "../error.h" // errorf

#define DEFINE_VECTOR_OF(T)                                                            \
	                                                                                   \
	void Vector_##T##_init  (Vector_##T *vector)                                       \
	{                                                                                  \
		vector->array    = NULL;                                                       \
		vector->length   = 0;                                                          \
		vector->capacity = 0;                                                          \
	}                                                                                  \
	                                                                                   \
	bool Vector_##T##_resize(Vector_##T *vector)                                       \
	{                                                                                  \
		vector->capacity = vector->capacity == 0 ? 1 : vector->capacity * 2;           \
		vector->array    = realloc(vector->array, vector->capacity * sizeof(T));       \
		                                                                               \
		if (vector->array == NULL)                                                     \
		{                                                                              \
			const char *desc = strerror(errno);                                        \
			errorf("failure reallocating memory\n[%c%s]", tolower(desc[0]), &desc[1]); \
			                                                                           \
			return true;                                                               \
		}                                                                              \
		                                                                               \
		return false;                                                                  \
	}                                                                                  \
	                                                                                   \
	void Vector_##T##_deinit(Vector_##T *vector)                                       \
	{                                                                                  \
		free(vector->array);                                                           \
		                                                                               \
		vector->length   = 0;                                                          \
		vector->capacity = 0;                                                          \
	}                                                                                  \
	                                                                                   \
	bool Vector_##T##_append(Vector_##T *vector, T item)                               \
	{                                                                                  \
		if (vector->length == vector->capacity)                                        \
			if (Vector_##T##_resize(vector))                                           \
				return true;                                                           \
		                                                                               \
		vector->array[vector->length++] = item;                                        \
	}                                                                                  \

// ! GENERIC VECTOR DEFINITIONS.

#include "../lexer.h"   // Token

DEFINE_VECTOR_OF(char ) // string.h
DEFINE_VECTOR_OF(Token)
