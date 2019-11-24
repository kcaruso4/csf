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
* Prints the hexvalue of the char provided
* Parameters:
*   ch - char value
*
* Returns:
*   a printible char value that correlates to the parameter
*       - if the paramenter is not a printible char a '.' is returned
*/
char print_hex(unsigned char ch) {
    if (isprint(ch)) {
        printf("%02x ", ch);
        return ch;
    }
    else {
        printf("%02x ", ch);
        return '.';
    }
}

/**
* Iterates through the char pointer passed into the function,
* prints the hex value of each char, prints any necessary whitespace
* for proper formatting, and prints the chars pointed at.
*
* Parameters:
*   chars - a pointe to a C string
*   pos - the hex position of the first char in the C string relavtive to
*   the input
*/

void char_hex_print(char *chars, int pos) {
    //prints the hexval of the position
    printf("%08x: ", pos);

    //prints the hexval for each char
    for (unsigned int i = 0; i < strlen(chars); i++) {
        chars[i] = print_hex(chars[i]);
    }

    //add space to output if requried
    for (unsigned int i = 0; i < 16 - strlen(chars); i++) {
        printf("   ");
    }

    //prints the C string
    printf(" %s\n", chars);
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
     char temp_str[HEXDUMP_BUFSIZE + 1];
     while (fgets(buf, HEXDUMP_BUFSIZE + 1, in) != NULL) {

         //used to ignore newline that stops fgets from reading all 16 char if necessary
         while (strlen(buf) < HEXDUMP_BUFSIZE) {
             fgets(temp_str, HEXDUMP_BUFSIZE + 1 - strlen(buf), in);
             if (ferror(in)) {
                 fprintf(stderr, "Data could not be read\n");
                 return 1;
             }
             else if (feof(in)) {
                 char_hex_print(buf, start_position);
                 return 0;
             }
             else {
                 strcat(buf, temp_str);
                 memset(temp_str, '\0', HEXDUMP_BUFSIZE + 1);
             }
         }
         //prints the hexvals of the chars and the chars
         char_hex_print(buf, start_position);
         memset(buf, '\0', HEXDUMP_BUFSIZE + 1);
         start_position += 16;
     }
     if (ferror(in)) {
         fprintf(stderr, "Data could not be read\n");
         return 1;
     }
    return 0;

}
