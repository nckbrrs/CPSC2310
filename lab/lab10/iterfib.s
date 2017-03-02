/*
	1) 46

	2) yes because changing from signed to unsigned int increases the possible
		values to print from (2^31 - 1) to (2^32 - 1)

	3) fib.s average time: 8.2963 seconds
		iterfib.s average time: 0.014 seconds
*/	
	.text
	.align	2
fib:
	push    {r5-r8, lr}     @ save any register used besides {r0-r3}
	@ CODE HERE
	
	cmp r0, #0					@ if test number is not 0, branch
	bne not_zero				@ if not, return

	pop	{r5-r8, pc}			@ restore registers and pop lr to pc

not_zero:
	cmp r0, #1					@ if test number is not 1, branch
	bne not_one					@ if not, return

	pop	{r5-r8, pc}			@ restore registers and pop lr to pc

not_one:
	mov	r5, #2				@ use r5 as a counter, initialize to 2
	mov	r6, #0				@ use r6 as Fn-2, current value is 0
	mov	r7, #1				@ use r7 as Fn-1, current value is 1

loop:	

	add	r8, r6, r7			@ current sum = Fn-2 + Fn-1
	mov	r6, r7				@ Fn-2 = Fn-1
	mov	r7, r8				@ Fn-1 = current sum

	add	r5, #1				@ increment counter
	cmp	r5, r0				@ if counter is less than argument, keep looping
	ble	loop

	mov	r0, r8				@ move final result into r0 to be returned
	pop	{r5-r8,pc}			@ restore registers and pop lr to pc

test:
    push   {r4, lr}

   						 @ call fib on given number
	mov    r4, r0
	bl     fib

							@ print the answer
	mov    r1, r4
	mov    r2, r0
	ldr    r0, =.LC0
	bl     printf

	pop    {r4, pc}
	
	.global main
main:
	push   {r4, lr}

							@ call 4 test cases
	mov    r0, #0
	bl     test

	mov    r0, #1
	bl     test

	mov    r0, #6
	bl     test

	mov    r0, #10
	bl     test

	mov	r0, #40
	bl	test

	pop    {r4,  pc}

	.section .rodata
	.align 2
.LC0:
	.ascii "Element %d (zero-based) in the Fibonacci sequence is %d\012\000"
