#pragma once

#ifndef _NULL_H
#define _NULL_H

#include "__version.h"

#define NULL (void *) 0

#ifdef  __C23
#define NULL nullptr
#endif

#endif // header guard
