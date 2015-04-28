#include "zmalloc.h"

struct foo {
	int x;
	struct foo * next;
};

int main(int argc, char ** argv){
	struct foo * test = zmalloc(sizeof(struct foo));
	struct foo * test1 = zmalloc(sizeof(struct foo));
	struct foo * test2;
	fprintf(stdout,"test @ %d\n",(int)test);
	fprintf(stdout,"test1 @ %d\n",(int)test1);
	zfree(test1);
	test2 = zmalloc(sizeof(struct foo));
	fprintf(stdout,"test2 @ %d\n",(int)test2);
	test->next = test2;
	//test1->next = test2;
	test->x = 5;
	//test1->x = 10;
	test2->x = 15;
	fprintf(stdout,"%d\t",test->x);
	//fprintf(stdout,"%d\t",test1->x);
	fprintf(stdout,"%d\n",test2->x);
	return 0;
}
