#pragma once

#include <string.h>  // strlen
#include <stdbool.h> // bool true false

#include "vector.h" // DECLARE_PRIMITIVE_VECTOR_T

DECLARE_PRIMITIVE_VECTOR_T(char)

typedef Vector_char String;

void String_init  (String *this);
void String_deinit(String *this);

bool String_resize(String *this);
bool String_append(String *this, char ch);

bool String_has(const String *this, char ch);

bool String_eq(const String *this, const String *string);

// extra methods

bool String_eq_cstr(const String *this, const char *string);
