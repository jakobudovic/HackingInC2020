#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




void addvectorBR(int *r, const int *a, const int *b, unsigned int len){
	unsigned int i;
	
	printf("%d\n", sizeof(i));

	for(i = 0; i < len; i++){
		
		// printf("%p\t a[%d]=%d    b[%d]=%d\n", (a+i), i, a[i], i, b[i]);
		r[i] = a[i] + b[i];
	}
}

void addvector(int *r, const int *a, const int *b, unsigned int len){
	unsigned int i;
	
	for(i = 0; i < len; i++){
		*(r+i) = *(a+i) + *(b+i);
	}
}


int memcmpBits(const void *s1, const void *s2, size_t n){

	// This works with bit shifting lol, Bits not Bytes uwu

	char* p1 = s1;
	char* p2 = s2;
	printf("h\n");s1

	for (int i = 0; i < (int)n; ++i){
		printf("prvi for loop izveden v iteraciji: %d\n", i);
		char c1 = *(p1+i);
		char c2 = *(p2+i);

		printf("c1: %d    c2: %d\n", c1, c2);

		// we check all 8 bits
		for (int j = 0; j < 8; ++j){
			uint8_t bit1 = ((c1 << j) & 10000000);
			uint8_t bit2 = ((c2 << j) & 10000000);

			printf("%d %d\n", bit1, bit2);

			if (bit1 != bit2){
				if (bit1 > bit2){	// s1 > s2
					return 1;
				}
				else{
					return -1;		// s2 > s1
				}
			}
		}
		// assign new char/Byte to c1 and c2
	}

	return 0;
} 

int memcmp1(const void *s1, const void *s2, size_t n){

	
	printf("n je %d\n", n);
	for (int i = 0; i < n; ++i){

		unsigned char byte1 = *((unsigned char*)s1 + i);
		unsigned char byte2 = *((unsigned char*)s2 + i);
		// uint8_t* p1 = s1 + i;
		// uint8_t* p2 = s2 + i;

		printf("iteration %d: %d, %d\n", i, byte1, byte2);


		if (byte1 != byte2){
			if (byte1 < byte2)
				return -1;
			else 
				return 1;
		}

	}

	return 0;
}

int memcmp_backwards(const void *s1, const void *s2, size_t n){

	
	printf("n je %d\n", n);
	printf("%p\n", s1);
	printf("next address : %p\n", (unsigned char*)s1 + 1);

	for (int i = n-1; i > -1; --i){

		unsigned char byte1 = *((unsigned char*)s1 + i);
		unsigned char byte2 = *((unsigned char*)s2 + i);
		// uint8_t* p1 = s1 + i;
		// uint8_t* p2 = s2 + i;

		printf("iteration %d: %d, %d\n", i, byte1, byte2);


		if (byte1 != byte2){
			if (byte1 < byte2)
				return -1;
			else 
				return 1;
		}

	}

	return 0;
}


int main(){

	/*
	int v1[3] = {1, 2, 3};
	int v2[3] = {4, 5, 6};
	int* r;
	r = (int*) malloc(sizeof(int) *3);

	// addvector(r, v1, v2, 3);
	*/


	
	int a;
	int b;
	scanf("%d %d", &a, &b);

	printf("===========\n");
	int rez = memcmp1(&a, &b, sizeof(a));
	printf("===========\n");
	printf("%d\n", rez);
	if (rez == 1){
		printf("%d is bigger than %d\n", a, b);
	}
	else if (rez == -1)	{
		printf("%d is smaller than %d\n", a, b);
	}
	else
		printf("numbers are equal\n");
	

	// free(r);
	return 0;
}