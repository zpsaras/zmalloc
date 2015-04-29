/***************************************************************
 *
 *	Stupid memory allocator. Plans to have GC.
 *			A lot of help comes from
 *	-| danluu.com/malloc-tutorial/ |-
 *		Much of the initial code is nearly identical to his
 *		Much thanks to him for presenting the material in a
 *		simple manner but without making it a toy. This is
 *		exactly what I needed to begin looking into this stuff!
 *
 **************************************************************/
#ifndef zmalloc_H
#define zmalloc_H

#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>

typedef struct header {
	unsigned int size;
	struct header * next;
	int free;
} header_t;

#define MIN_ALLOC_SIZE 4096
#define HEADER_SIZE sizeof(header_t)

header_t *list_head = NULL;

header_t * find_free(header_t **last, size_t size){
	header_t * current = list_head;
	while(current && !(current->size == size && current->free == 1)){
		*last = current;
		current = current->next;
	}
	return current;
}

header_t * get_more(header_t * last, size_t size){
	header_t * block;
	//void * block;
	void * after; //Must be void* because sbrk may return -1

	block = sbrk(0); //Top of heap before alloc
	after = sbrk(size);
	assert((void*)block == after);

	if(after == (void*) -1){
		return NULL;
	}

	if(last){
		last->next = block;
	}
	block->size = size;
	block->next = NULL;
	block->free = 0;
	return (header_t*)block;
}

void * zmalloc(size_t size){
	header_t * block;
	header_t * last;
	int count;

	if (size <= 0){
		return NULL; //Standards
	}
	
	// We want alloc sizes to be in multiples of pages
	if (size + HEADER_SIZE < MIN_ALLOC_SIZE){
		size = MIN_ALLOC_SIZE;
	} else {
		for(count = 0; (count * MIN_ALLOC_SIZE) > (size + HEADER_SIZE); count++);
		size = count * MIN_ALLOC_SIZE;
	}


	if(!list_head){
		block = get_more(NULL, size);
		if(!block) {
			return NULL;
		}
		list_head = block;
	} else {
		last = list_head;
		block = find_free(&last, size);
		if(!block){
			block = get_more(last, size);
			if(!block){
				return NULL;
			}
		} else {
			block->free = 0;
		}
	}

	return (block+1);
}

header_t * get_block_ptr(void * ptr){
	return (header_t*) ptr - 1;
}

void zfree(void * ptr){
	header_t * block;

	if(!ptr){
		return;
	}

	block = get_block_ptr(ptr);
	assert(block->free == 0);
	
	block->free = 1;
}
	
//TODO: calloc and realloc
#endif




