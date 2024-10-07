#include "shell.h"            // header

#include <stdio.h>            // putc fprintf stderr
#include <stdarg.h>           // va_list va_start va_arg va_end
#include <string.h>           // strlen

#include "error.h"            // errorf
#include "utilities/string.h" // String String_create String_append String_deinit

bool shellf(int argc, char *argv[], Shell_Mark mark_rule, size_t index_count, ...)
{
	va_list  args;
	va_start(args, index_count);

	Vector_int indices;
	Vector_int_create(&indices);

	for (size_t i = 0; i < index_count; i++)
		if (Vector_int_append(&indices, va_arg(args, int)))
		{
			errorf("failure creating shell");
			return true;
		}

	size_t shell_length = 7;

	String marks;
	String_create(&marks);

	putc('\n', stderr);
	fprintf(stderr, "$      ");

	size_t last_index = argc - 1;

	for (size_t i = 0; i < argc; i++)
	{
		size_t length = strlen(argv[i]);

		bool indexed = Vector_int_has(&indices, i);

		if (mark_rule == Shell_Mark_other_indices)
			indexed = !indexed;

		if (indexed)
		{
			size_t diff = shell_length - marks.length;

			for (size_t i = 0; i < diff; i++)
				if (String_append(&marks, ' '))
					return true;

			for (size_t i = 0; i < length; i++)
				if (String_append(&marks, '^'))
					return true;
		}

		fprintf(stderr, "%s", argv[i]);
		shell_length += length;

		if (i != last_index) // prevent trailing space
		{
			putc(' ', stderr);
			shell_length++; // is this necessary or can we add +1 to the other one?
		}
	}

	fprintf(stderr, "\n%.*s\n", marks.length, marks.array);

	String_deinit(&marks);
	Vector_int_deinit(&indices);

	va_end(args);
	return false;
}
