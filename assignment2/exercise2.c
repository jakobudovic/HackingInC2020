#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
	

	bool t = true;
	bool f = false;
	printf("size of bool: %zuB\n", sizeof(bool));
	printf("true: 0x%x \nfalse: 0x%x\n", t, f);

	t = 0x123;
	printf("\nt = 0x123;\n");
	printf("t = 0x%x and t = %d\n", t, t);

	// anything above 0 is TRUE or 1 in integer.
	// 0 is FALSE.

	return 0;
}