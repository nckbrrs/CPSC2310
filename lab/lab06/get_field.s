	.global main

main:
	push {r7, lr}
	sub sp, sp, #16
	add r7, sp, #0

	ldr r0, =0x12345678       /* put the source value in r0 */
	ldr r2, =0x7              /* put the location of the field's lsb in r2 */
	ldr r3, =0x8              /* put the size of field in r3 */
	
/* Beginning of your code */
	mov r4, #1 				/* put 1 in r4 */
	lsl r4, r4, r3 		/* shift the 1 by size of field bits */
	sub r4, r4, #1 		/* create series of 1s that is size of field */ 
	lsl r4, r4, r2 		/* shift the mask by (position of lsb) bits */ 
	
/* End of your code */
	and r1, r4, r0 		/* perform bitwise and on source and mask */
	lsr r1, r1, r2			/* shift result so that lsb is at position 0 */

/* show output on screen */
    ldr r0, =prt_line	
	bl printf
	add r7, r7, #16
	mov sp, r7
	pop {r7, pc}

	.size main, .-main
	.section .rodata

prt_line: .asciz "0x%X\n"
