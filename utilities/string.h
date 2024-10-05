#pragma once

#include <string.h>  // strlen
#include <stdbool.h> // bool true false

#include "vector.h" // DECLARE_VECTOR_OF

DECLARE_VECTOR_OF(char)

typedef Vector_char String;

void String_init  (String *string);
void String_deinit(String *string);

bool String_resize(String *string);
bool String_append(String *string, char item);

// extra methods

bool String_eq(const String *string_l, const char *string_r);
