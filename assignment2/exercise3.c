#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
	
    short x = 0;
    short xInverted = ~x;
    short y = -0;

    if (xInverted == y){
    	printf("This computer doesn’t use two-complement representation.\n");
    }
    else{
    	printf("This computer uses two-complement representation.\n");
    }

	

	return 0;
}