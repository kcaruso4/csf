/**
* Keilani Caruso
* kcaruso4
* hw3
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**
* This file reads up to 16 binary data bytes from the
* standard input and prints one line of output for each
* input byte. Each output byte is the disassembly of the
* input byte as a SCRAM instruction
*/

int main() {
    char* instruction[] = {"HLT", "LDA", "LDI", "STA", "STI", "ADD", "SUB", "JMP", "JMZ"};

    unsigned char readin[17];
    FILE* in = stdin;
    int index = 0;
    int done = 0;

    while(!done) {
        if(index > 16) {
            printf("Read a max of 16 bytes\n");
            return 1;
        }
        int in_val = fgetc(in);
        if(in_val == EOF) {
            done = 1;
        }
        else {
            readin[index++] = in_val;
        }
    }
    if(index > 0) {
        int start = 0;
        unsigned char name, data;
        while(start < index) {
            name = readin[start] / 16;
            data = readin[start] << 4;
            data = data >> 4;
            if(name > 8) {
                printf("%x: ??? %x\n", start, data);
            }
            else {
                printf("%x: %s %x\n", start, instruction[name], data);
            }
            start++;
        }
    }
    return 0;
}
