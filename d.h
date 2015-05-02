#include_next<float.h>

#ifndef _MINGW_FLOAT_H_
#define _MINGW_FLOAT_H_

/* All the headers include this file. */
#include <_mingw.h>

void deletetail(char *inptr);
void deletetailr(char *inptr);

/* Control word masks for unMask */
#define	_MCW_EM		0x0008001F	/* Error masks */
#define	_MCW_IC		0x00040000	/* Infinity */
#define	_MCW_RC		0x00000300	/* Rounding */
#define	_MCW_PC		0x00030000	/* Precision */

void _fpreset (void);
void fpreset (void);

double __cdecl_chgsign	(double);
double __cdecl_copysign (double, double);