#include "zmalloc.h"

#define malloc(x) zmalloc(x)
#define free(x) zfree(x)
