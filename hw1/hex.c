/*
 * This file produces a hexdump based on the given input
 * file or command line inputs
 * CSF Fall 2019
 * Homework 1
 * Keilani Caruso
 * kcaruso4@jh.edu
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* The number of data bytes corresponding to one line of hexdump output. */
#define HEXDUMP_BUFSIZE 16

/* TODO: function prototypes */


/**
* Iterates through the char pointer passed into the function,
* prints the hex value of each char, prints any necessary whitespace
* for proper formatting, and prints the chars pointed at.
*
* Parameters:
*   chars - a pointe to a C string
*   pos - the hex position of the first char in the C string relavtive to
*   the input
*   length - the length of the C string being passed in to print
*/

void char_hex_print(char *chars, int pos, int length) {
    //prints the hexval of the position
    printf("%08x: ", pos);

    //prints the hex value of the chars
    for (int i = 0; i < length; i++) {
        printf("%02x ", (unsigned char) chars[i]);
    }

    //prints added space for fomratting if needed
    if (length < HEXDUMP_BUFSIZE) {
        for (int i = length; i < HEXDUMP_BUFSIZE; i++) {
            printf("   ");
        }
    }

    //for second space between hex vals and chars
    printf(" ");

    //prints printible characts or .
    for (int i = 0; i < length; i++) {
        if (isprint(chars[i])) {
            printf("%c", chars[i]);
        }
        else {
            printf(".");
        }
    }
    printf("\n");
}

int main(int argc, char **argv) {
    FILE *in;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [<filename>]\n", argv[0]);
        fprintf(stderr, "Reads from standard input if <filename> is omitted\n");
        return 1;
    }

    if (argc == 1) {
        in = stdin;
    }
    else {
        in = fopen(argv[1], "rb");
        /* TODO: report error and exit if input file couldn't be opened */
        if (ferror(in)) {
            fprintf(stderr, "File could not be opened\n");
            return 1;

        }
    }

    char buf[HEXDUMP_BUFSIZE + 1]; /* storage for data read from input */
    /*
     * TODO: read data from the file handle called "in" and print a hexdump
     * of its contents
     */

     int start_position = 0;
     int curr = 0;
     int last = 0;
     //char temp_str[HEXDUMP_BUFSIZE + 1];
     while(!feof(in)) {
         if (curr == HEXDUMP_BUFSIZE) {
             char_hex_print(buf, start_position,curr);
             start_position += 16;
             curr = 0;
         }
         buf[curr++] = fgetc(in);

         last = curr;
     }


     if (last != 1) {
         char_hex_print(buf, start_position, last - 1);
     }

    return 0;

}
