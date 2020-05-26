#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[1]) {
    char command[10];
    char buffer[100];
    strcpy(command, "/bin/ls");
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(1);
    }

    strcpy(buffer, argv[1]);

    printf("* [INFO] The value of command is: \"%s\"\n", command);
    
    system(command);

    return 0;
}
