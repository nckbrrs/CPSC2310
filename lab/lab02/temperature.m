						comment(`this program prints the Celsius to Fahrenheit')
						comment(`conversions for the range from -40C to 120C in') 
						comment(`steps of 10 degrees')

bipush(-40)			comment(`load -40 onto the stack and store it in local')
istore_1				comment(`register 1')

label(loop)

iload_1				comment(`load current C temp onto stack')

bipush(9)			comment(`compute C-F conversion (F = ((C*9)/5) + 32)')
imul
bipush(5)
idiv
bipush(32)
iadd
istore_2				comment(`store Fahrenheit temp in local register 2')

iconst_1				comment(`print local register 1, the current C temp')
invokevirtual(1)	comment(`and local register 2, the converted F temp')
iconst_2	
invokevirtual(2)

iinc(1, 10)			comment(`increment local register 1 (C temp) by 10')

iload_1				comment(`push current C temp onto stack')
bipush(120)			comment(`if top of stack is <=0 (C temp <= 120) goto loop')
isub					
ifle(loop)

return
