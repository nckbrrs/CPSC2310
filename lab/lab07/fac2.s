	.global	fact
fact:
	mov   r1, #1       @ put an initial value of 1 into r1, which will represent
								@	the program's current factorial value

here:
	cmp   r0, #1       @ check if r0 = 0
	beq   there        @ if so, branch to "there" and if not, keep looping

	mul   r1, r0, r1   @ r1 = r0 * r1
	sub   r0, r0, #1   @ decrement r0
	b     here         @ go back to start of loop

there:
	mov   r0, r1       @ place final factorial value into r0

	bx    lr

	.size	fact, .-fact

	.align   2
	.section .rodata
fmt_str:
	.ascii  "The factorial of %d is %d\012\000"

	.text
	.align  2
	.global main
main:
	push  {r3, lr}

	mov   r0, #10
	bl    fact

	mov   r2, r0
	mov   r1, #10
	ldr   r0, =fmt_str
	bl    printf

	mov   r0, #0

	pop  {r3, pc}

	.size    main, .-main
	.ident   "GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section .note.GNU-stack,"",%progbits
