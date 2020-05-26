#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

// source 
// data types in C: https://www.tutorialspoint.com/cprogramming/c_data_types.htm

int main( int argc, char *argv[] )  {

   char filename[] = "/dev/urandom";
   char buf[2];
   FILE *fp;
   uint16_t buff; 
    
   if ((fp = fopen(filename, "rb")) == NULL)
   {
      printf("Unable to open file: %s\n", filename);
      return EXIT_FAILURE;
   }
    
	// for (int i = 0; i < 10; ++i){
	
   	do{
			if (fread(buf, 1, 2, fp) == 2){
				buff = (unsigned char) buf[0];
				buff = buff << 8; // shift 8 bites to the left, make space for the other number
				buff += (unsigned char) buf[1];
				printf("%04x \n", (int) buff);
				// printf("%04x %04x\n", (unsigned char) buf[0], (unsigned char) buf[1]);
				// printf("===========================\n");
		}
   	} while(buff != 0x002a);

   	fclose(fp);
   	return 0;
}