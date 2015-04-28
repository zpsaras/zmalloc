ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

all:
	gcc -L$(ROOT_DIR) -Wl,-rpath=$(ROOT_DIR) main.c -o test -lzmalloc

precomp:
	gcc -c -Wall -fpic zmalloc_def.h

shared:
	gcc -c -Wall -fpic zmalloc_def.c
	gcc -shared -o libzmalloc.so zmalloc_def.o

clean:
	rm -rf *.so *.o *.h.gch test
