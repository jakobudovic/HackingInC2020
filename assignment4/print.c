#include <stdlib.h>

void print(char* string){
	printf(string);
}


int main(int argc, char* argv[1]) {

	long bla = 0xDEADC0DECAFEF00D;
	print(argv[1]);
/*
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
*/
    return 0;
}
