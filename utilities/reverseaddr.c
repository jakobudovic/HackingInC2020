#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#include "functions.h"

int main(int argc, char* argv[]) {
    regex_t regex;
    int ret;
    if ((ret = regcomp(&regex, "^0x[a-f0-9]{1,}$", REG_ICASE | REG_EXTENDED))) {
        char errorbuf[100];
        regerror(ret, &regex, errorbuf, sizeof(errorbuf));
        fprintf(stderr, "Compiling regex failed: %s!\n", errorbuf);
        return 255;
    }

    char* addr_string = argv[1];
    int returncode = 0;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s 0xADDRESS\n", argv[0]);
        fprintf(stderr, "Prints the address as the actual bytes in little-endian order\n");
        fprintf(stderr,
                "Don't be surprised when it appears there is no output, it might just be "
                "unreadable. Try piping the output to `xxd`.\n");
        returncode = 1;
        goto end;
    }

    ret = regexec(&regex, addr_string, 0, NULL, 0);
    if (ret != 0) {
        char errorbuf[100];
        regerror(ret, &regex, errorbuf, sizeof(errorbuf));
        fprintf(stderr, "Regex match failed: %s\n", errorbuf);
        returncode = ret;
        goto end;
    }

    uintptr_t address = strtol(addr_string, NULL, 16);
    print_address_little_endian(address);

end:
    regfree(&regex);

    return returncode;
}
