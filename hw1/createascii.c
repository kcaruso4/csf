#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char**argv) {
    for (unsigned int i = 0; i < 256; i++) {
        printf("%c\n", i);
    }
}