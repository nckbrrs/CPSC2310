comment(`		code that implements the loop							')
comment(`			sum = 0;													')
comment(`			for (i = 1; i <= 10; i++)							')
comment(`				sum = sum + i;										')
comment(`			}															')

	word(sum,0)
	word(i,1)
	word(one,1)
	word(ten,10)

label(start)

label(loop)

	load(sum)	comment(`	sum = sum + i							')
	add(i)
	store(sum)

	load(i)		comment(`	i = i + 1								')
	add(one)
	store(i)

	load(i)
	sub(ten)
	ble0(loop)	comment(` 	go back to loop if i <= 10			')

label(done)

	print(sum)
	halt

comment(`		start execution at label start					')

	end(start)
