/*
 * hexFuncs.S
 * [Your name]
 * [Your email]
 *
 * This file should implement functions to be called from your
 * main function (in hex.S).
 *
 * You can (and should!) write unit tests for these functions, to
 * the extent possible.  See hexTests.c
 */

	.section .text

/*
 * addLongs function (this is just an example function)
 */
	.globl addLongs
addLongs:
	subq $8, %rsp                 /* align stack pointer */

	movq %rsi, %rax               /* move second parameter to %rax */
	addq %rdi, %rax               /* add first parameter to second */
	/* the sum is now in %rax */

	addq $8, %rsp                 /* restore stack pointer */
	ret

/* TODO: add other functions */

/* vim:ft=gas:
 */
