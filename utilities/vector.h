// !
// ! ALL VECTOR DECLARATIONS MUST ALSO BE DECLARED IN vector.c
// !

#pragma once

#include <stddef.h>  // size_t
#include <stdbool.h> // bool

//
// note: which members are declared in which macros in vector.c
// differs from which members are declared in which macros here
//
// eg. void Vector_##_T_##_deinit(Vector_##_T_ *vector);
//
//     > in vector.h, declared in UNIVERSAL_VECTOR_T
//
//     > in vector.c, declared in PRIMITIVE_VECTOR_T and
//                                DEVELOPED_VECTOR_T because
//
//     although the function signatures are the same the way each is
//     implemented depending on the vector type is different
//

//
// member functions that return true on failure do so so that
// error handling code can be ran without the need to perform a
// not operation:
//
// if (Vector_int_append(&vector, 1))
// {
//     Vector_int_deinit(&vector);
//
//     /* other error handling code */
// }
//

#define DECLARE_UNIVERSAL_VECTOR_T(_T_)                                               \
	                                                                                  \
	typedef struct Vector_##_T_                                                       \
	{                                                                                 \
		_T_   *array;                                                                 \
    	                                                                              \
		size_t length;                                                                \
		size_t capacity;                                                              \
	} Vector_##_T_;                                                                   \
	                                                                                  \
	void Vector_##_T_##_init  (Vector_##_T_ *this);                                   \
	void Vector_##_T_##_deinit(Vector_##_T_ *this);                                   \
	                                                                                  \
	/* returns true on failure in which case destructor must still be called */       \
	bool Vector_##_T_##_resize(Vector_##_T_ *this);                                   \
	                                                                                  \
	bool Vector_##_T_##_eq    (const Vector_##_T_ *this, const Vector_##_T_ *vector); \

// !
// ! USE ON PRIMITIVE DATATYPES
// ! eg. DECLARE_PRIMITIVE_VECTOR_T(int)
// !

#define DECLARE_PRIMITIVE_VECTOR_T(_T_)                                               \
	                                                                                  \
	DECLARE_UNIVERSAL_VECTOR_T(_T_)                                                   \
	                                                                                  \
	/* returns true on failure in which case destructor must still be called */       \
	bool Vector_##_T_##_append(      Vector_##_T_ *this, _T_ item);                   \
	                                                                                  \
	bool Vector_##_T_##_has   (const Vector_##_T_ *this, _T_ item);                   \

// !
// ! USE ON STRUCTS AND DEFINE THE FOLLOWING METHODS WHERE X IS THE STRUCT NAME
// !
// ! void X_deinit(X *)       :  destructor
// ! bool X_eq    (X *, X *)  :  operator==
// !

#define DECLARE_DEVELOPED_VECTOR_T(_T_)                                               \
	                                                                                  \
	DECLARE_UNIVERSAL_VECTOR_T(_T_)                                                   \
	                                                                                  \
	bool Vector_##_T_##_append(      Vector_##_T_ *this, const _T_  item);            \
	                                                                                  \
	bool Vector_##_T_##_has   (const Vector_##_T_ *this, const _T_ *item);            \

// comment prevents `backslash-newline at end of file` warning
