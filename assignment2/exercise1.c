#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// source: https://www.geeksforgeeks.org/how-to-print-a-variable-name-in-c/
#define getName(name)  #name

int main() {
	
	int32_t a = 1;	
	int16_t b = 2;
	unsigned char c = 3;
	int8_t d = 4;
	unsigned long long e = 5;
	short f[3] = {6, 6, 6};
	long g = 7;
	unsigned long int h = 8;
	uint8_t i = 9;
	
	
	fprintf(stderr, "address\t\tvariable\tvalue\tsizeof\tnext_addr\n");
	printf("%14p %9s %12" PRId32 "%9zu %12p\n", (void*)&a, getName(a), a, sizeof(a), (void*)(&a + 1));	// sizeof() return size_t, so %zu
	printf("%14p %9s %12hu %8zu %12p\n", (void*)&b, getName(b), b, sizeof(b), (void*)(&b + 1));
	printf("%14p %9s %12" PRId16 "%9zu %12p\n", (void*)&c, getName(c), c, sizeof(c), (void*)(&c + 1));
	printf("%14p %9s %12" PRId8 "%9zu %12p\n", (void*)&d, getName(d), d, sizeof(d), (void*)(&d + 1));
	printf("%14p %9s %12llu %8zu %12p\n", (void*)&e, getName(e), e, sizeof(e), (void*)(&e + 1));
	printf("%14p %9s %12hu %8zu %12p\n", (void*)&f, getName(f), *f, sizeof(f), (void*)(&f + 1));
	printf("%14p %9s %12ld %8zu %12p\n", (void*)&g, getName(g), g, sizeof(g), (void*)(&g + 1));
	printf("%14p %9s %12lu %8zu %12p\n", (void*)&h, getName(h), h, sizeof(h), (void*)(&h + 1));
	printf("%14p %9s %12d %8zu %12p\n", (void*)&i, getName(i), i, sizeof(i), (void*)(&i + 1));
	
	return 0;
}
