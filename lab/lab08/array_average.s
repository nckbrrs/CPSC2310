	.syntax unified
	.section .text.startup,"ax",%progbits
	.global main

main:
	push    {r4, r5, lr}		@ pushes the values of r4 and r5 onto stack
				 	@ to "save" them, since their values will
					@ be changed in this function. lr is pushed
					@ onto the stack so main can pop its value
					@ to the pc when it is over to return
					@ to the correct location

	sub     sp, sp, #64		@ makes room on the stack for the 16 ints
					@ each of which have a size of 4-bytes

	mov     r4, sp			@ puts the current sp, which is the starting
					@ address of the array to be created
					@ into r4

	ldr     r5, =array_values	@ loads address where array values
					@ are located into r5

	ldmia   r5!, {r0, r1, r2, r3}	@ loads the first 4 values of r5,
					@ which are the first 4 values of the array,
					@ into r0, r1, r2, and r3
					@ the ! makes it so that r5's
					@ newly-incremented value is saved

	stmia   r4!, {r0, r1, r2, r3}	@ stores the values of r0, r1, r2, and r3,
					@ which are the first 4 values of the array,
					@ into r4
					@ the ! makes it so that r4's 
					@ newly-incremented value is saved

	ldmia   r5!, {r0, r1, r2, r3}	@ loads the next 4 values of r5,
					@ which are the next 4 values of the array,
					@ into r0, r1, r2, and r3
					@ the ! makes it so that r5's
					@ newly-incremented value is saved

	stmia   r4!, {r0, r1, r2, r3}	@ stores the values of r0, r1, r2, and r3,
					@ which are the next 4 values of the array,
					@ into r4
					@ the ! makes it so that r4's 
					@ newly-incremented value is saved

	ldmia   r5!, {r0, r1, r2, r3}	@ loads the next 4 values of r5,
					@ which are the next 4 values of the array,
					@ into r0, r1, r2, and r3
					@ the ! makes it so that r4's 
					@ newly-incremented value is saved

	stmia   r4!, {r0, r1, r2, r3}	@ stores the values of r0, r1, r2, and r3
					@ which are the next 4 values of the array
					@ into r4.
					@ the ! makes it so that r4's 
					@ newly-incremented value is saved

	ldmia   r5, {r0, r1, r2, r3}	@ loads the final 4 values of r5,
					@ which are the final 4 values of the array,
					@ into r0, r1, r2, and r3

	stmia   r4, {r0, r1, r2, r3}	@ stores the values of r0, r1, r2, and r3
					@ which are the next 4 values of the array
					@ into r4.

					@ r4 now holds the entire array

	mov     r2, #0			@ put 0 into r2, which will act as the sum
	mov     r3, #0			@ put 0 into r3, which will act as the counter


.loop:
	ldr     r1, [sp, r3]		@ put the stack pointer, offset by 
					@ the current value of r3 (which will be
					@ the next value of the array), into r1

	add     r2, r2, r1		@ sum = sum + r1 (i.e. sum = sum + a[i])

	add     r3, r3, #4		@ increment r3 by #4, so it can 
					@ be used to access the next element of the 
					@ array in the next iteration

	cmp     r3, #64 		@ compare r3 to 64 to see if the "counter"
					@ of the loop is at the end of the array

	bne     .loop			@ if not at the end of the array, 
					@ continue looping

	ldr     r0, =.print_string	@ load the print format string into r0

	mov     r1, r2, lsr #4		@ place r2, the sum / 16 (i.e. the average), 
					@ into r1 to prepare for printing

	bl      printf			@ call printf to print sum

	add     sp, sp, #64		@ restore stack pointer for later use

	pop     {r4, r5, lr}		@ restore values of r4, r5, and lr for later use

	bx      lr			@ branches to lr, which sets pc to 
					@ the address of the next function
	.size   main, .-main

	.section  .rodata

	@ You may put read only data, similar what was used in lab7, here

array_values:
	.word 20
	.word 10
	.word 14
	.word 18
	.word 2
	.word 5
	.word 8
	.word 18
	.word 4
	.word 12
	.word 17
	.word 18
	.word 21
	.word 54
	.word 71
	.word 13
	
	.section  .rodata.str1.1,"aMS",%progbits,1

	@ You may put your print string here
.print_string:
	.ascii "average = %d\012\000"

.end_program:
	.ident    "GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section  .note.GNU-stack,"",%progbits
