/*
 * hex.S
 * [Your name]
 * [Your email]
 *
 * This file should have only the main function for the hex program.
 * It should call functions that you have defined in hexFuncs.S.
 */

	.section .text

	.globl main
main:
	subq $8, %rsp                 /* adjust stack pointer */

	/* TODO: add your code here! */

	movq $0, %rax
	addq $8, %rsp                 /* adjust stack pointer */
	ret

/* vim:ft=gas:
 */
