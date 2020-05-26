#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void magic_function();

char* p1;

int main (void){

	char x = 0;
	p1 = &x;

	int bytes = (2048*2048);
	
	for (int i = 0; i < bytes; ++i){
		*(p1-i-1) = 0;
	}

	// https://stackoverflow.com/questions/2814188/c-array-of-pointers-delete-or-delete

	magic_function();

	for (int i = bytes-1; i >= 0; --i){
		int val = *(p1-i-1);
		if(val != 0){
			printf("stack size: %d\n", i);
			break;
		}
	}
	return 0;
}
