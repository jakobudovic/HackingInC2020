#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// help: https://stackoverflow.com/questions/8680220/how-to-get-the-value-of-individual-bytes-of-a-variable

int main (void){

	short i = 0x1234;
	char x = -127;
	long sn1 = 1045403;
	long sn2 = 1049877;
	int y[2] = {0x11223344,0x44332211};

	fprintf(stderr, "address\t\tcontent (hex)\tcontent (dec)\n");
	fprintf(stderr, "-------------------------------------------\n");

	printf("i:\n");
	// i
	for (int j = 0; j < (int)sizeof(i); ++j){
		unsigned char byte = *((unsigned char*)&i + j);
		printf("%14p\t \t0x%x \t\t %d\n", (void*)&i+j, byte, byte);
	}

	printf("\nx:\n");

	// x
	for (int i = 0; i < (int)sizeof(x); ++i){
		unsigned char byte = *((unsigned char*)&x + i);
		printf("%14p\t \t0x%x \t\t %d\n", (void*)&x + i, byte, byte);
	}

	printf("\nsn1:\n");

	// sn1  HERE we need unsigned char AKA uint8_t because of the weird student number. I used uint8_t, but unsigned char works too.
	for (int i = 0; i < (int)sizeof(sn1); ++i){
		uint8_t* byte = *((uint8_t*)&sn1 + i);
		printf("%14p\t \t0x%02x \t\t %d\n", (void*)&sn1 + i, byte, byte);
	}

	printf("\nsn2:\n");

	// sn2  
	for (int i = 0; i < (int)sizeof(sn2); i++){
		uint8_t byte = *((uint8_t*)&sn2 + i);
		printf("%14p\t \t0x%02x \t\t %d\n", (void*)&sn2 + i, byte, byte);
	}

	printf("\ny:\n");

	// y[2]
	for (int i = 0; i < (int)sizeof(y); ++i){
		// printf("%dm %d\n", i, sizeof(0x11223344));
		unsigned char byte = *((unsigned char*)&y + i);
		printf("%14p\t \t0x%02x \t\t %d\n", (void*)&y + i, byte, byte);
	}	

	printf("\n");
	return 0;
}