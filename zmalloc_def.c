#ifndef __ZDEF
 #define __ZDEF

#include "zmalloc.c"

#define malloc(x) zmalloc(x)
#define free(x) zfree(x)
#define memset(x) zmemset(x)
#define calloc(x) zcalloc(x)

#endif
