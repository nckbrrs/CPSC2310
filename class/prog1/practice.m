	word(a,15)
	word(b,0)
	word(zero,0)
	word(one,1)

label(loop)

	load(a)
	sub(one)
	blt0(done)
	load(b)
	add(a)
	store(b)
	load(a)
	sub(one)
	store(a)
	ba(loop)

label(done)

	print(b)
	halt
	end(loop)
