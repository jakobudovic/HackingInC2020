#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	int32_t* p = 0x7fffb3cc3b20;
	int32_t x[4];
	x[0] = 23;
	x[1] = 42;
	x[2] = 5;
	x[3] = (1<<7);
	
	// 0x7fffb3cc3b20

	printf("%p\n",x); 				// prints 0x7ffb3cc3b20

	printf("%p\n", &x); 			// (a) 0x7ffb3cc3b20

	printf("%p\n", x+1); 			// (b) 0x7ffb3cc3b24

	printf("%p\n", &x+1); 			// (c) 0x7ffb3cc3b30

	printf("%d\n", *x); 			// (d) 

	printf("%d\n", *x+x[2]); 		// (e)

	printf("%d\n", *x+*(x+3)); 		// (f)

	return 0;
}
