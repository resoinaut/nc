#include "preprocessor.h" // header

#include <stdio.h>        // FILE EOF rewind
#include <stdbool.h>      // bool false

#include "error.h"        // errnof
#include "errormessage.h" // failure_reading_src_file

bool preprocess(FILE *tmp_file, FILE *src_file)
{
	int ch;

	while ((ch = getc(src_file)) != EOF)
	{
		if (putc(ch, tmp_file) != EOF)
			continue;

		errnof(failure_writing_tmp_file);
		return true;
	}

	if (ferror(src_file))
	{
		errnof(failure_reading_src_file);
		return true;
	}

	rewind(tmp_file);

	// EOF

	return false;
}
