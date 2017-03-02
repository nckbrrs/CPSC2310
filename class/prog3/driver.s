/*

	Nicholas Barrs (nbarrs)
	CPSC 2310-002
	Program Assignment 3
	March 23, 2016

	driver.s runs a loop, which reads in 3 integers from the user  to represent
	a, b, and c in the quadratic equation a(x^2) + bx + c = 0, and then calls
	the discrim function with those three integers as parameters and prints its
	result, 3 times.

*/

i			.req r4                       @ rename local variables.

			.file "driver.s"
			.section .text
			.global main
			.type main, %function

main:
			push		{r4, lr}             @ save registers.
			sub		sp, sp, #12          @ make room for 3 ints on stack.
			mov		i, #0                @ initialize loop counter to 0.

loop:
			ldr		r0, =prompt1         @ print prompt.
			bl			printf

			ldr		r0, =scanfmt         @ scan user input onto the stack
			add		r1, sp, #0           @ using the scanfmt format string.
			add		r2, sp, #4
			add		r3, sp, #8
			bl 		scanf	

			ldr		r0, [sp, #0]         @ load user input into argument
			ldr		r1, [sp, #4]         @ variables and call discrim function.
			ldr		r2, [sp, #8]
			bl			discrim

			mov 		r1, r0               @ print result of discrim function
			ldr		r0, =prntfmt         @ using prntfmt format string.
			bl			printf
																
			add		i, i, #1             @ increment counter.
			cmp		i, #3                @ if counter < 3, keep looping.
			blt		loop	
		
			.unreq	i                    @ release names of local variables
			add		sp, sp, #12          @ restore stack pointer, r4,
			mov		r0, #0               @ and return 0.
			pop		{r4, pc}	
						
			.section	.rodata

prompt1:	.asciz	"Enter 3 integers (a,b,c) for the equation a(x^2)+bx+c = 0:\n"
scanfmt:	.asciz	"%d %d %d"	
prntfmt:	.asciz	"\nThe discriminant of your equation is %d\n-------------\n\n"
