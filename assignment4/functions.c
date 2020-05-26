#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// colour code magic
#define RED "\033[0;31m"
#define GREEN  "\033[0;32m"
#define NC  "\033[0m"

int check_passphrase(char* passphrase) {
  char buffer[100];
  strcpy(buffer, passphrase);
  if(strcmp(passphrase, "the magic words are squeamish ossifrage") == 0)
    return 1;
  return 0;
}

void launch_shell() {
  printf(GREEN "Launching shell." NC "\n");
  system("/bin/bash");
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <passphrase>\n", argv[0]);
    exit(0);
  }

  printf("* [DEBUG] Your input: %s\n", argv[1]);
  printf("* [DEBUG] The function launch_shell is at %p\n", launch_shell);

  if (check_passphrase(argv[1])) {
      launch_shell();
      exit(0);
  } else {
      fprintf(
        stderr, 
        RED "Wrong password. This incident will be reported. "
        "https://xkcd.com/838/" NC "\n");
  }

  return 1;
}
