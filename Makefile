ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

# The test target includes an example of how to compile zmalloc to a shared lib

test:
	gcc -L$(ROOT_DIR) -Wl,-rpath=$(ROOT_DIR) main.c -o test -lzmalloc

precomp:
	gcc -c -Wall -fpic zmalloc_def.h

shared:
	gcc -c -Wall -fpic zmalloc.c
	gcc -shared -o libzmalloc.so zmalloc.o

shared_redef:
	gcc -c -Wall -fpic zmalloc_def.c
	gcc -shared -o libzmalloc.so zmalloc_def.o

clean:
	rm -rf *.so *.o *.h.gch test
