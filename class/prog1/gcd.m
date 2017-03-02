							comment(`Nicholas Barrs (nbarrs)')
							comment(`CPSC 2310-002')
							comment(`Program 1')
							comment(`Jan 25, 2016')
							comment(`---------------')
							comment(`GCD.m : computes greatest common divisor of')
							comment(`any two integers defined at beginning of code')

	word(a,60)			comment(`a and b are the two integers whose GCD')
	word(b,24)			comment(`this program is computing')
	word(one, 1)
	word(temp,0)
	word(remainder,0)
	word(GCD,0)

label(loop)

	load(b)				comment(`check if b is currently == 1; if so then')
	sub(one)				comment(`a and b are relatively prime, so branch to done')
	beq0(done)

	load(a)				comment(`if a mod b == 0, b is the GCD, so')	
	div(b)				comment(`branch to done')
	mul(b)
	store(temp)
	load(a)
	sub(temp)
	beq0(done)

	store(remainder)	comment(`if not, store b in a, store')
	load(b)				comment(`a mod b's result in b, and branch to')
	store(a)				comment(`beginning of loop')
	load(remainder)
	store(b)
	ba(loop)

label(done)

	load(b)				comment(`current value of b is GCD of a and b')
	store(GCD)
	print(GCD)
	halt

	end(loop)			comment(`start execution at label start')
