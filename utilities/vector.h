// ! ALL VECTOR DECLARATIONS MUST ALSO BE DEFINED IN THE
// ! IMPLEMENTATION FILE VECTOR.C

#pragma once

#include <stddef.h>   // size_t
#include <stdbool.h>  // bool

#define DECLARE_VECTOR_OF(T)                              \
	                                                      \
	typedef struct                                        \
	{                                                     \
		T     *array;                                     \
    	                                                  \
		size_t length;                                    \
		size_t capacity;                                  \
	} Vector_##T;                                         \
	                                                      \
	void Vector_##T##_init  (Vector_##T *vector);         \
	void Vector_##T##_deinit(Vector_##T *vector);         \
	bool Vector_##T##_resize(Vector_##T *vector);         \
	bool Vector_##T##_append(Vector_##T *vector, T item); \

// comment prevents `backslash-newline at end of file` warning
