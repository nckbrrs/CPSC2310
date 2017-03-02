init:
	push  {fp}
	
	sub   sp, sp, #8
	mov   fp, sp

	str   r1, [fp]
	str   r2, [fp, #4]

	ldmia fp, {r1, r2}
	stmia r0, {r1, r2}

	add   fp, fp, #8
	mov   sp, fp

	pop   {fp}

	bx    lr

box_init:
	push	{fp}

	sub	sp, sp, #12
	mov	fp, sp

	str	r1, [fp]
	str	r2, [fp, #4]
	str	r3, [fp, #8]

	ldmia	fp, {r1, r2, r3}
	stmia r0, {r1, r2, r3}

	add	fp, fp, #12
	mov	sp, fp

	pop	{fp}
	bx		lr


zero:
	push  {fp}

	sub   sp, sp, #8
	mov   fp, sp

	mov   r3, #0
	str   r3, [fp]
	str   r3, [fp, #4]

	ldmia fp, {r1, r2}
	stmia r0, {r1, r2}

	add   fp, fp, #8
	mov   sp, fp

	pop   {fp}

	bx    lr

	.global main
main:
	push   {fp, lr}

	sub    sp, sp, #20
	mov    fp, sp

	mov    r0, fp
	mov    r1, #34
	mov    r2, #-3
	bl     init

    ldr    r0, =fmtstr	
	ldr    r1, [fp]
	ldr    r2, [fp, #4]
	bl     printf

	mov    r0, fp
	bl     zero

	ldr    r0, =fmtstr
	ldr    r1, [fp]
	ldr    r2, [fp, #4]
	bl     printf

	mov	r0, fp
	mov	r1, #45
	mov	r2, #17
	mov	r3, #3
	bl		box_init

	ldr	r0, =boxfmtstr
	ldr	r1, [fp]
	ldr	r2, [fp, #4]
	ldr	r3, [fp, #8]
	bl		printf

	add    sp, sp, #20

	pop    {fp, pc}

fmtstr:
	.ascii "The members of the structure dot are %d, %d\012\000"
	
boxfmtstr:
	.ascii "The members of the structure box are %d, %d, %d\012\000"
