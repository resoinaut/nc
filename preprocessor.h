#pragma once

#include <stdio.h>             // FILE

#include "utilities/string.h"  // String_*
#include "utilities/vector.h"  // DECLARE_DEVELOPED_VECTOR_T

DECLARE_DEVELOPED_VECTOR_T(String)

// returns true on failure
int preprocess(FILE *output, FILE *source, const char *filename);
