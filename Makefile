ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

# The test target includes an example of how to compile zmalloc to a shared lib

test:
	gcc -L$(ROOT_DIR) -Wl,-rpath=$(ROOT_DIR) main.c -o test -lzmalloc

shared:
	gcc -c -Wall -fpic zmalloc.c
	gcc -shared -o libzmalloc.so zmalloc.o

shared_redef:
	gcc -c -Wall -fpic zmalloc_def.c
	gcc -shared -o libzmalloc.so zmalloc_def.o

clean:
	rm -rf *.so *.o *.h.gch test

help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... test"
	@echo "  -> Compiles a vanilla main.c"
	@echo "... shared"
	@echo "  -> Creates a shared library"
	@echo "... shared_redef"
	@echo "  -> Creates a shared library that redefines a few common malloc's (Easily test with pre-existing code)"
	@echo "... clean"
	@echo "  -> Standard rm of all generated files"
	@echo "... help"
	@echo "  -> You're here!"

