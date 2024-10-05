#pragma once

#include "vector.h" // DECLARE_VECTOR_OF

DECLARE_VECTOR_OF(char)

#define String        Vector_char

#define String_init   Vector_char_init
#define String_deinit Vector_char_deinit
#define String_resize Vector_char_resize
#define String_append Vector_char_append
