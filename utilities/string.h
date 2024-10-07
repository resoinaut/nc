#pragma once

#include <string.h>  // strlen
#include <stdbool.h> // bool true false

#include "vector.h" // DECLARE_PRIMITIVE_VECTOR_T

DECLARE_PRIMITIVE_VECTOR_T(char)

typedef Vector_char String;

// note: String_resize not necessary

#define String_create Vector_char_create
#define String_deinit Vector_char_deinit
#define String_append Vector_char_append
#define String_has    Vector_char_has
#define String_eq     Vector_char_eq

// extra methods

bool String_eq_cstr(const String *this, const char *string);
