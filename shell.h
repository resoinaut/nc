#pragma once

#include "utilities/vector.h" // DECLARE_PRIMITIVE_VECTOR_T

DECLARE_PRIMITIVE_VECTOR_T(int)

typedef enum Shell_Mark
{
	Shell_Mark_given_indices,
	Shell_Mark_other_indices,
} Shell_Mark;

void shellf(int argc, char *argv[], const Vector_int *indices, Shell_Mark mark_rule);
