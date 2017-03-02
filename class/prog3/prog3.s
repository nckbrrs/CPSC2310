/*

	Nicholas Barrs (nbarrs)
	CPSC 2310-002
	Program Assignment 3
	March 23, 2016

	prog3.s holds the discrim function, which takes in three integers a, b, and c
	as input and calculates and returns the value of (b*b) - (4*a*c).

*/

a_				.req r4                          @ rename registers for use as
b_				.req r5                          @ local variables.
bsq			.req r6
c_				.req r7
discrim		.req r8

				.section .text
				.global discrim
				.type discrim, %function

/* discrim:

	description:
	- takes in three integers a, b, and c, which represent a, b, and c in the
	quadratic equation a(x^2) + bx + c = 0, and calculates and returns the
	discriminant, (b*b)-(4*a*c)

	input parameters:
	- r0: a in the quadratic equation
	- r1: b in the quadratic equation
	- r2: c in the quadratic equation

	return value:
	- the discriminant of the quadratic equation, (b*b)-(4*a*c)

	other output parameters:
	- none

	effect/output:
	- none apart from return value:

	method:
	- simple algebra

	typical calling sequence:
	- in main, read 3 integers in from user onto the stack, 
	then move those values into r0, r1, and r2, respectively,
	then call discrim

	local register usage:
	- r4: holds value of a
	- r5: holds value of b
	- r6: holds value of (b*b)
	- r7: holds value of c
	- r8: holds value of discriminant

*/

discrim:
				push 		{r4-r8, lr}             @ save registers.

				mov		a_, r0                  @ move parameters into local vars.
				mov		b_, r1
				mov		c_, r2

				mul		bsq, b_, b_             @ bsq = (b*b).
				mul		discrim, a_, c_         @ discrim = (a*c).
				lsl		discrim, #2             @ discrim = (4*a*c).
				sub		discrim, bsq, discrim   @ discrim = (b*b)-(4*a*c).
				mov		r0, discrim

				.unreq a_                        @ release register names.
				.unreq b_
				.unreq bsq
				.unreq c_
				.unreq discrim

				pop {r4-r8, pc}                  @ restore register values and
                                             @ return 0.
