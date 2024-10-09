#pragma once

#include <stdbool.h>          // bool

#include "utilities/vector.h" // DECLARE_PRIMITIVE_VECTOR_T

DECLARE_PRIMITIVE_VECTOR_T(int)

typedef enum Shell_Mark
{
	Shell_Mark_given_indices,
	Shell_Mark_other_indices,
} Shell_Mark;

// returns true on failure
bool shellf(int argc, char *argv[], Shell_Mark mark_rule, size_t index_count, ...);
