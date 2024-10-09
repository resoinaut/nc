#include "preprocessor.h"     // header

#include <ctype.h>            // isspace
#include <stdio.h>            // FILE EOF rewind
#include <locale.h>           // size_t
#include <stdlib.h>           // free

#include "error.h"            // errnof
#include "errormessage.h"     // failure_reading_src_file

#include "utilities/string.h" // String_*
#include "utilities/errorhandling.h" // TRY

void _preprocessor_handle_failure_reading_src_file()
{
	errnof(failure_reading_src_file);
}

/// parses src_file into a vector of whitespace
/// separated strings until the first LF or EOF
/// @returns 0 on success and 1 on failure
int _preprocessor_parse_directive(Vector_String *args, FILE *src_file)
{
	int ch;

	String arg;
	String_create(&arg);

	while ((ch = getc(src_file)) != EOF)
	{
		if (ch == '\n')
			break;

		if (isspace(ch))
		{
			// in case of consecutive whitespace
			if (arg.length == 0)
				continue;

			TRY(Vector_String_append(args, arg));

			// reset arg without invoking destructor
			String_create(&arg);

			continue;
		}

		TRY(String_append(&arg, ch));
	}

	if (ferror(src_file))
	{
		String_deinit(&arg);
		_preprocessor_handle_failure_reading_src_file();
		return 1;
	}

	// move last arg to args

	// in case of trailing whitespace or zero args
	if (arg.length > 0)
		Vector_String_append(args, arg);

	// arg isnt destructed because it was moved to args

	return 0;
}

/// writes to tmp_file the preprocessed version of src_file
/// @returns 0 on success and 1 on failure
int preprocess(FILE *tmp_file, FILE *src_file, const char *filename)
{
	int ch;
	size_t row = 1;

	fprintf(tmp_file, "#line 1 %s\n", filename);

	while ((ch = getc(src_file)) != EOF)
	{
		if (ch == '#')
		{
			Vector_String args;
			Vector_String_create(&args);

			TRY(_preprocessor_parse_directive(&args, src_file));

			if (args.length == 0)
			{
				errnof("expected preprocessor directive");
				return 1;
			}

			String *directive = &args.array[0];

			if (String_eq_cstr(directive, "include"))
			{
				if (args.length > 2)
				{
					errorf("expected 1 argument to include directive and received %i", args.length - 1);
					return 1;
				}

				String *filepath = &args.array[1];

				if (filepath->array[0] != '"')
				{
					errorf("expected argument 1 of include directive to be a string");
					return 1;
				}

				if (filepath->array[filepath->length - 1] != '"')
				{
					errorf("string argument of include directive is unterminated");
					return 1;
				}

				fprintf(tmp_file, "#line 1 %.*s\n", (int)(filepath->length), filepath->array);

				Slice filename_slice = String_slice(filepath, 1, filepath->length - 1);
				char *include_path   = slice_to_cstr(&filename_slice);

				if (include_path == NULL)
					return 1;

				FILE *included_file = fopen(include_path, "r");

				free(include_path);

				if (included_file == NULL)
				{
					errnof(failure_reading_src_file);
					return 1;
				}

				while ((ch = getc(included_file)) != EOF)
					putc(ch, tmp_file);

				if (ferror(included_file))
				{
					errnof(failure_reading_src_file);
					return 1;
				}

				if (fclose(included_file))
				{
					errnof(failure_closing_src_file);
					return 1;
				}

				fprintf(tmp_file, "#line %zu %s", ++row, filename);

				continue;
			}
			else
			{
				errorf("unrecognised preprocessor directive '%.*zu'", directive->length, directive->array);
				return 1;
			}

			if (feof(src_file))
				break;

			continue;
		}

		if (ch == '\n')
			row++;

		if (putc(ch, tmp_file) != EOF)
			continue;

		errnof(failure_writing_tmp_file);
		return true;
	}

	if (ferror(src_file))
		goto handle_failure_reading_src_file;

	// EOF

	rewind(tmp_file);

	return false;

	// error handling

	handle_failure_reading_src_file:

	errnof(failure_reading_src_file);
	goto return_failure;

	return_failure:

	return true;
}
