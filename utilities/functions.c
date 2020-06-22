#include "functions.h"
#include <stdio.h>

void print_address_little_endian(uintptr_t address) {
    for (unsigned long i = 0; i < sizeof(uintptr_t) && address; i++) {
        char byte = (unsigned char)(address & 0xFF);
        printf("%c", byte);
        address >>= 8;
    }
}

