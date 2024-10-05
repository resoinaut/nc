#include "vector.h"   // header

#include <ctype.h>    // tolower
#include <errno.h>    // errno
#include <locale.h>   // NULL
#include <stddef.h>   // size_t
#include <stdlib.h>   // realloc free
#include <string.h>   // strerror
#include <stdbool.h>  // bool true false

#include "../error.h" // errorf

#define DEFINE_IS_UNIVERSAL_VECTOR_METHODS(T)                                          \
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

// ! NONITERATIVE VECTOR METHODS DONT CALL CONSTRUCTORS OR
// ! DESTRUCTORS ON IT'S ITEMS

// ! USED IN VECTORS OF PRIMITIVE DATATYPES AND CLASSES WITHOUT
// ! CONSTRUCTORS AND DESTRUCTORS

// ! eg. DEFINE_NONITERATIVE_VECTOR_METHODS(int)

#define DEFINE_NONITERATIVE_VECTOR_METHODS(T)                  \
	void Vector_##T##_deinit(Vector_##T *vector)               \
	{                                                          \
		free(vector->array);                                   \
		                                                       \
		vector->length   = 0;                                  \
		vector->capacity = 0;                                  \
	}                                                          \
	                                                           \
	bool Vector_##T##_append(Vector_##T *vector, const T item) \
	{                                                          \
		if (vector->length == vector->capacity)                \
			if (Vector_##T##_resize(vector))                   \
				return true;                                   \
		                                                       \
		vector->array[vector->length++] = item;                \
	}                                                          \

// ! IS_ITERATIVE VECTOR METHODS CALL CONSTRUCTORS AND
// ! DESTRUCTORS ON IT'S ITEMS

// ! USED IN VECTORS OF CLASSES THAT USE CONSTRUCTORS AND
// ! DESTRUCTORS

// ! eg. DEFINE_IS_ITERATIVE_VECTOR_METHODS(Token)

#define DEFINE_IS_ITERATIVE_VECTOR_METHODS(T)                  \
	void Vector_##T##_deinit(Vector_##T *vector)               \
	{                                                          \
		for (size_t i = 0; i < vector->length; i++)            \
			T##_deinit(&vector->array[i]);                     \
		                                                       \
		free(vector->array);                                   \
		                                                       \
		vector->length   = 0;                                  \
		vector->capacity = 0;                                  \
	}                                                          \
	                                                           \
	bool Vector_##T##_append(Vector_##T *vector, const T item) \
	{                                                          \
		if (vector->length == vector->capacity)                \
			if (Vector_##T##_resize(vector))                   \
				return true;                                   \
			                                                   \
		vector->array[vector->length] = item;                  \
		T##_init(&vector->array[vector->length++]);            \
	}                                                          \

// ! GENERIC VECTOR DEFINITIONS

#include "../lexer.h"                     // Token

DEFINE_IS_UNIVERSAL_VECTOR_METHODS(char ) // for string.h
DEFINE_NONITERATIVE_VECTOR_METHODS(char )

DEFINE_IS_UNIVERSAL_VECTOR_METHODS(Token)
DEFINE_IS_ITERATIVE_VECTOR_METHODS(Token)
