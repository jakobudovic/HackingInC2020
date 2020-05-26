#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

// source 
// c read byte from file: https://cboard.cprogramming.com/c-programming/84251-read-2-bytes-file.html
// printf: https://icecube.wisc.edu/~dglo/c_class/printf.html


int main( int argc, char *argv[] )  {

   char filename[] = "/dev/urandom";
   char buf[1];
   FILE *fp;
    
   if ((fp = fopen(filename, "rb")) == NULL)
   {
      printf("Unable to open file: %s\n", filename);
      return EXIT_FAILURE;
   }
    
	// for (int i = 0; i < 10; ++i){
	
   	do{
			if (fread(buf, 1, 1, fp) == 1){
			printf("%d %u %x \n", (int) buf[0], buf[0], buf[0]);
		}
   	} while(buf[0] != 42);

   	fclose(fp);
   	return 0;
}