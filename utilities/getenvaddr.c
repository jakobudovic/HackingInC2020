#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <sys/personality.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#define COLOR_RED "\033[1;31m"
#define COLOR_DEFAULT "\033[0m"

#ifdef PRINT_BYTES
#include "functions.h"
#endif

int main(int argc, char* argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <environment var> <target program path>\n\n", argv[0]);
        fprintf(stderr,
                "This program computes where the requested environment variable would "
                "be if you were executing the other program. This allows you to inject "
                "shell code there.\n");
        fprintf(stderr,
                "You need to specify the path in the same way as you are "
                "executing the target program.\n\n");

#ifdef PRINT_BYTES
        fprintf(stderr,
                "This version of the program will print the address as bytes to "
                "stdout, so you can use it in attack scripts. Debug info is "
                "printed to stderr.\n\n");
#endif

        fprintf(stderr,
                "Of course, if ASLR is turned on for the target process, the "
                "address will be at a different location there.\n");
        exit(1);
    }

    int previous_personality = personality(0xffffffff);
    if ((previous_personality & ADDR_NO_RANDOMIZE) == 0) {
        fprintf(stderr, "⚠️ " COLOR_RED " ASLR is not disabled!" COLOR_DEFAULT "\n");
        fprintf(stderr, "⚡ Now disabling " COLOR_RED "only" COLOR_DEFAULT " for this process to get stable results.\n");
        fprintf(stderr, "💡 Use 'setarch $(uname -m) -R bash' to get a shell without ASLR\n");
        int rc = personality(previous_personality | ADDR_NO_RANDOMIZE);
        if (rc == -1) {
            perror("🚨" COLOR_RED "Disabling ASLR failed." COLOR_DEFAULT);
        } else {
            fprintf(stderr, "🔧 Restarting " COLOR_RED "only this" COLOR_DEFAULT " process without ASLR…\n");
            execv(argv[0], argv);
        }
    } else {
        fprintf(stderr, "✅ ASLR is disabled.\n");
    }

    char* ptr = getenv(argv[1]);
    if (ptr == NULL) {
        fprintf(stderr, "❌ Environment variable '%s' not found!", argv[1]);
        exit(2);
    }

    // Correct address for difference in paths/names of executables
    ptr += (strlen(argv[0]) - strlen(argv[2]))*2;

    // we print to stderr to not interfere with the address output
    fprintf(stderr, "🤖 %s will be at %p\n", argv[1], ptr);

#ifdef PRINT_BYTES
    print_address_little_endian((uintptr_t) ptr);
#endif

}
