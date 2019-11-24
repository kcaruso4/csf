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

/**
* Accepts a char and position of char
* prints the associated SCRAM instruction and data value
*/
void printSCRAM(char c[], int length) {
    //array of SCRAM instructions
    char* instruction[] = {"HLT", "LDA", "LDI", "STA", "STI", "ADD", "SUB", "JMP", "JMZ"};
    unsigned char name, data;
    int position = 0;
    while(position < length) {
        name = c[position] >> 4;
        data = c[position] << 4;
        data = data >> 4;
        if (name > 8 && name < 16) {
            printf("%x: ??? %x\n", position, data);
        }
        else {
            printf("%x: %s %x\n", position, instruction[name], data);
        }
        position++;
    }
}


int main(int argc, char** argv) {
    //checks to make sure you are only reading for the std in
    if(argc > 1 && *argv != NULL) {
        fprintf(stderr, "This program only reads from the stdin\n");
    }

    char readin[17]; //stores characters read in
    FILE *in = stdin; //sets stdiin to file pointer
    int position = 0; //keeps track of the position and length in readin
    char byte;

    if(!feof(in)) {
        byte = fgetc(in);
    }

    while(!feof(in)) {
        if(position == 16) {
            fprintf(stderr, "Too many input bytes\n");
            return 1;
        }
        readin[position++] = byte;
        byte = fgetc(in);
    }

    if (position > 0) {
        printSCRAM(readin, position);
    }
    return 0;
}
