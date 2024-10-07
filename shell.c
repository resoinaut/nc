#include "shell.h"            // header

#include <stdio.h>            // putc fprintf stderr
#include <string.h>           // strlen

#include "utilities/string.h" // String String_create String_append String_deinit

void shellf(int argc, char *argv[], const Vector_int *indices, Shell_Mark mark_rule)
{
	size_t shell_length = 7;

	String marks;
	String_create(&marks);

	putc('\n', stderr);
	fprintf(stderr, "$      ");

	size_t last_index = argc - 1;

	for (size_t i = 0; i < argc; i++)
	{
		size_t length = strlen(argv[i]);

		bool indexed = Vector_int_has(indices, i);

		if (mark_rule == Shell_Mark_other_indices)
			indexed = !indexed;

		if (indexed)
		{
			size_t diff = shell_length - marks.length;
			for (size_t i = 0; i < diff; i++) String_append(&marks, ' ');
			for (size_t i = 0; i < length; i++) String_append(&marks, '^');
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
}
