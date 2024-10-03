// TODO: split into multiple headers

// * TEMPORARY

// winnt.h

#define VOID void

typedef void *PVOID;

typedef PVOID HANDLE;

// windef.h

#define WINAPI __stdcall

typedef int BOOL;

typedef void  *LPVOID;
typedef DWORD *LPDWORD;

// intsafe.h

typedef unsigned long DWORD;

// winbase.h

#define STD_OUTPUT_HANDLE (DWORD) -11

// consoleapi.h

extern BOOL WINAPI WriteConsoleA(
	HANDLE      hConsoleOutput,
	const VOID *lpBuffer,
    DWORD       nNumberOfCharsToWrite,
    LPDWORD     lpNumberOfCharsWritten,
    LPVOID      lpReserved
);

// processenv.h

extern HANDLE WINAPI GetStdHandle(
	DWORD nStdHandle
);
