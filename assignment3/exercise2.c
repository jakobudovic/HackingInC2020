#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern void magic_function();

int main (void){

	int szt = sizeof(size_t);

	float max = 0;
	max = pow(2, szt*8);

	printf("Size of size_t data type: %d\n", szt);

	printf("One malloc can allocate at most %.0f bytes.\n", max);

	// gcc exercise2.c -o exercise2 -lm
	return 0;
}
