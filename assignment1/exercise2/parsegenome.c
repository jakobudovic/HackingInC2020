#include <stdio.h>
#include <stdlib.h>

// https://stackoverflow.com/questions/42720100/how-to-read-line-wise-from-a-file-in-c-ubuntu
// https://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm



int main( int argc, char *argv[] )  {

	FILE* fp = fopen(argv[1],"r");

	if(fp == NULL){
   perror("fopen");
   exit(1);
	}
	else{
		printf("File is opened.\n");
	}

	char c;
	int ROWS = 500;
	int COLS = 100;

	int i = 0;
	int j = 0;

	int numA = 0;
	int numC = 0;
	int numG = 0;
	int numT = 0;

	// ACGT
	while((c = fgetc(fp)) != EOF){
		
		if (c == '\n'){	// newline
			if(j != COLS){
				printf("File is in the wrong format!\n");
				printf("Wrong number of letters in line %d. I found %d instead of %d.\n", i+1, j, COLS);
				return 1;
			}
			else{
				j = 0;
			}
			i++;
		}
		else if(c == 'A' || c == 'C' || c == 'G' || c == 'T'){
			j++;
			if (c == 'A'){
				numA++;
			}
			else if (c == 'C'){
				numC++;
			}
			else if (c == 'G'){
				numG++;
			}
			else{
				numT++;
			}
		}
		else{printf("Wrong number of letters in line %d. I found %d instead of %d.\n", i+1, j, COLS);
			printf("Something went wrong, unexpected character: %c in line %d, column %d\n", c, i+1, j+1);
			exit(1);
		}
	}

	if (i == ROWS){
		printf("We have an input of the right form!\n");
		printf("===================\n");
		printf("A: %d\n", numA);
		printf("C: %d\n", numC);
		printf("G: %d\n", numG);
		printf("T: %d\n", numT);
		printf("===================\n");
	}
	else{
		printf("Wrong number of rows: %d, instead of %d,\n", i+1, ROWS);
		return 1;
	}

	fclose(fp);
	return 0;
}