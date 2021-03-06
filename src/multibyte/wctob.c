#include <wchar.h>
#include <stdlib.h>
#include "internal.h"
#include <stdio.h>

int wctob(wint_t c)
{
	if (c < 128U) return c;
	if (MB_CUR_MAX==1 && IS_CODEUNIT(c)) return (unsigned char)c;
	return EOF;
}
