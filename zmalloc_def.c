#include "zmalloc.c"

#define malloc(x) zmalloc(x)
#define free(x) zfree(x)
