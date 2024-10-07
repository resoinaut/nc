// !
// ! ALL VECTOR DECLARATIONS MUST ALSO BE DECLARED IN vector.h
// !

#include "vector.h"   // header

#include <locale.h>   // NULL
#include <stddef.h>   // size_t
#include <stdlib.h>   // realloc free
#include <stdbool.h>  // bool true false

#include "../error.h" // errnof

//
// note: which members are declared in which macros in vector.h
// differs from which members are declared in which macros here
//
// eg. void Vector_##_T_##_deinit(Vector_##_T_ *vector);
//
//     > in vector.h, declared in VECTOR_T_UNIVERSAL_MEMBERS
//
//     > in vector.c, declared in DECLARE_PRIMITIVE_VECTOR_T and
//                                DECLARE_DEVELOPED_VECTOR_T because
//
//     although the function signatures are the same the way each is
//     implemented depending on the vector type is different
//

#define DEFINE_UNIVERSAL_VECTOR_T(_T_)                                               \
	                                                                                 \
	void Vector_##_T_##_create(Vector_##_T_ *vector)                                 \
	{                                                                                \
		vector->array    = NULL;                                                     \
		vector->length   = 0;                                                        \
		vector->capacity = 0;                                                        \
	}                                                                                \
	                                                                                 \
	bool Vector_##_T_##_resize(Vector_##_T_ *this)                                   \
	{                                                                                \
		this->capacity = this->capacity == 0 ? 1 : this->capacity * 2;               \
		_T_ *new_array = realloc(this->array, this->capacity * sizeof(_T_));         \
		                                                                             \
		if (new_array == NULL)                                                       \
		{                                                                            \
			errnof("failure reallocating memory");                                   \
			return true;                                                             \
		}                                                                            \
		                                                                             \
		this->array = new_array;                                                     \
		return false;                                                                \
	}                                                                                \
	                                                                                 \
	/* the only difference between primitive vector append and */                    \
	/* developed vector append is whether item is const or not */                    \
	/* so only one implementation is needed and it is const to */                    \
	/* be able to work with any one of them */                                       \
	                                                                                 \
	bool Vector_##_T_##_append(Vector_##_T_ *this, const _T_ item)                   \
	{                                                                                \
		if (this->length == this->capacity)                                          \
			 if (Vector_##_T_##_resize(this))                                        \
			 	return true;                                                         \
		                                                                             \
		this->array[this->length++] = item;                                          \
		return false;                                                                \
	}                                                                                \

// !
// ! USE ON PRIMITIVE DATATYPES
// ! eg. DECLARE_PRIMITIVE_VECTOR_T(int)
// !

#define DEFINE_PRIMITIVE_VECTOR_T(_T_)                                               \
	                                                                                 \
	DEFINE_UNIVERSAL_VECTOR_T(_T_)                                                   \
	                                                                                 \
	void Vector_##_T_##_deinit(Vector_##_T_ *this)                                   \
	{                                                                                \
		free(this->array);                                                           \
		                                                                             \
		this->array    = NULL;                                                       \
		this->length   = 0;                                                          \
		this->capacity = 0;                                                          \
	}                                                                                \
	                                                                                 \
	bool Vector_##_T_##_has   (const Vector_##_T_ *this, _T_ item)                   \
	{                                                                                \
		for (size_t i = 0; i < this->length; i++)                                    \
			if (this->array[i] == item)                                              \
				return true;                                                         \
		                                                                             \
		return false;                                                                \
	}                                                                                \
	                                                                                 \
	bool Vector_##_T_##_eq    (const Vector_##_T_ *this, const Vector_##_T_ *vector) \
	{                                                                                \
		if (this->length != vector->length)                                          \
			return false;                                                            \
		                                                                             \
		for (size_t i = 0; i < this->length; i++)                                    \
			if (this->array[i] != vector->array[i])                                  \
				return false;                                                        \
		                                                                             \
		return true;                                                                 \
	}                                                                                \

// !
// ! USE ON STRUCTS AND DEFINE THE FOLLOWING METHODS WHERE X IS THE STRUCT NAME
// !
// ! void X_deinit(X *)       :  destructor
// ! bool X_eq    (X *, X *)  :  operator==
// !

#define DEFINE_DEVELOPED_VECTOR_T(_T_)                                               \
	                                                                                 \
	DEFINE_UNIVERSAL_VECTOR_T(_T_)                                                   \
		                                                                             \
	void Vector_##_T_##_deinit(Vector_##_T_ *this)                                   \
	{                                                                                \
		for (size_t i = 0; i < this->length; i++)                                    \
			_T_##_deinit(&this->array[i]);                                           \
		                                                                             \
		free(this->array);                                                           \
		                                                                             \
		this->array    = NULL;                                                       \
		this->length   = 0;                                                          \
		this->capacity = 0;                                                          \
	}                                                                                \
	                                                                                 \
	bool Vector_##_T_##_has   (const Vector_##_T_ *this, const _T_ *item)            \
	{                                                                                \
		for (size_t i = 0; i < this->length; i++)                                    \
			if (_T_##_eq(&this->array[i], item))                                     \
				return true;                                                         \
		                                                                             \
		return false;                                                                \
	}                                                                                \
	                                                                                 \
	bool Vector_##_T_##_eq    (const Vector_##_T_ *this, const Vector_##_T_ *vector) \
	{                                                                                \
		if (this->length != vector->length)                                          \
			return false;                                                            \
		                                                                             \
		for (size_t i = 0; this->length; i++)                                        \
			if (!_T_##_eq(&this->array[i], &vector->array[i]))                       \
				return false;                                                        \
		                                                                             \
		return true;                                                                 \
	}                                                                                \

// ! DECLARATIONS

#include "../shell.h"  // Vector_int
#include "string.h"    // Vector_char
#include "../lexer.h"  // Vector_Token Token

DEFINE_PRIMITIVE_VECTOR_T(int  )
DEFINE_PRIMITIVE_VECTOR_T(char )

DEFINE_DEVELOPED_VECTOR_T(Token)
