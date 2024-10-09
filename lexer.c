#include "lexer.h"            // header

#include <ctype.h>            // isalpha isalnum
#include <stdio.h>            // EOF FILE getc
#include <string.h>           // strcmp
#include <stdbool.h>          // bool true false

#include "error.h"            // errorf errnof
#include "errormessage.h"     // failure_reading_tmp_file
#include "utilities/string.h" // String_*
