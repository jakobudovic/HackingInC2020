#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char *s1 = malloc(9);
	if (s1 == NULL) return 1;
	char *s2 = malloc(9);
	if (s2 == NULL) return 1;

	strcpy(s1,"s1049877");
	strcpy(s2,"s1045403");
	
	// char *s1 = "s1049877";
	// char *s2 = "s1045403";
	
	// do your attack

	// 32 - 8 = 24
	// So we need to terminate the null \0 char at the end of the string.
	// This is a char at *(s1+8). But for some reason we needed to also change
	// the next 23 characters totaling 24 of them, changing them to something else 
	// (dash or space for example). We don't really know why is that. Why not just the 8th char.

	for (int i = 0; i < 24; ++i){
		*(s1+8+i) = ' ';
	}
	*(s1+8) = ' ';

	printf("student 1: %s\n", s1);
	printf("student 2: %s\n\n", s2);
	printf("%p\n%p\n", s1, s2);

	return 0;
}
