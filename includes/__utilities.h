#pragma once

#ifndef _UTILITIES_H
#define _UTILITIES_H

// macro __C90
//       __C99
//       __C11
//       __C17
//       __C23

		#define __C90

#ifdef __STDC_VERSION__

	#if __STDC_VERSION__ >= 199901L
		#define __C99
	#endif

	#if __STDC_VERSION__ >= 201112L
		#define __C11
	#endif

	#if __STDC_VERSION__ >= 201710L
		#define __C17
	#endif

	#if __STDC_VERSION__ >= 202311L
		#define __C23
	#endif

#endif

// macro __restrict

// the restrict keyword was added in C99
// the macro contains restrict if v. C99+ otherwise nothing

#define __restrict
#ifdef  __C99
#define __restrict restrict
#endif

#endif // header guard
