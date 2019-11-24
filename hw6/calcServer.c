#include <stdio.h>      /* for snprintf */
#include "csapp.h"
#include "calc.h"

/* buffer size for reading lines of input from user */
#define LINEBUF_SIZE 1024

int chat_with_client(struct Calc *calc, int infd, int outfd);

int main(int argc, char **argv) {
	/* TODO: implement this program */
	//should only be two args passed in from the command line
	if (argc != 2) {
		return 1;
	}

	int servsock = Open_listenfd(argv[1]);

	if (servsock == -1 || servsock == -2) {
		return 1;
	}

	//new calc struct
	struct Calc *calc = calc_create();

	int check = 1;
	while(check) {
		int clisock = Accept(servsock, NULL, NULL);
		check = chat_with_client(calc, clisock, clisock);
		Close(clisock);
	}

	calc_destroy(calc);
	return 0;
}

int chat_with_client(struct Calc *calc, int infd, int outfd) {
	rio_t in;
	char linebuf[LINEBUF_SIZE];

	/* wrap standard input (which is file descriptor 0) */
	rio_readinitb(&in, infd);

	/*
	 * Read lines of input, evaluate them as calculator expressions,
	 * and (if evaluation was successful) print the result of each
	 * expression.  Quit when "quit" command is received.
	 */

	while (1) {
		ssize_t n = rio_readlineb(&in, linebuf, LINEBUF_SIZE);
		if (n <= 0) {
			/* error or end of input */
			return 1;
		} else if (strcmp(linebuf, "quit\n") == 0 || strcmp(linebuf, "quit\r\n") == 0) {
			/* quit command */
			return 1;
		}
		else if (strcmp(linebuf, "shutdown\n") == 0 || strcmp(linebuf, "shutdown\r\n") == 0) {
			/*shutdown command*/
			return 0;
		}
		else {
			/* process input line */
			int result;
			if (calc_eval(calc, linebuf, &result) == 0) {
				/* expression couldn't be evaluated */
				rio_writen(outfd, "Error\n", 6);
			} else {
				/* output result */
				int len = snprintf(linebuf, LINEBUF_SIZE, "%d\n", result);
				if (len < LINEBUF_SIZE) {
					rio_writen(outfd, linebuf, len);
				}
			}
		}
	}
	return 0; //should never be reached because while loop is either always true or returns 0 (shutdown) or 1 (error)
}
