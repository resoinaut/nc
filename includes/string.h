#pragma once

#ifndef _STRING_H
#define _STRING_H

#include "__size_t.h"

size_t strlen(const char *string)
{
	size_t i = 0;
	while (string[i] != '\0') i++;

	return i;
}

#endif // header guard
