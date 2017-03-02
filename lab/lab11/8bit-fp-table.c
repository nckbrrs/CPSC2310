#include <stdio.h>
  
int main()
{
	int sign, exp, fraction, significand;
	int i;
	float f;
	float prev = 0;
	
	int s, x, fff, a, b;

	for (i = 0; i < 256; i++)
	{

	/* begin your code */

	// extract bit fields
	fraction = (i & 7);
	exp = ((i >> 3) & 15);
	sign = ((i >> 7) & 1);
	
	// if exp is 0, treat it like a 1 and then apply bias
	if (exp == 0) { 
		exp -= 7; 
		x = 0;
	}
	
	// otherwise, treat it as normal and apply bias
	else  { 
		exp -= 8;
		x = 1;
	}

	// if sign bit is 0, number is positive. otherwise, number is negative.
	if (sign == 0) s = 1; 
	else s = -1;

	// compute significand, and adjust exp accordingly
	fff = fraction;
	significand = (x << 3) + fff;
	exp -= 3;
	f = significand;

	// if exponent is positive, multiply by 2 repeatedly to get value
	if (exp > 0)
		for (a=0; a<exp; a++) f *= 2;

	// if exponent is negative, divide by 2 repeatedly to get value
	else
		for (b=0; b>exp; b--) f *= 0.5;

	// apply sign
	f *= s;

	/* end your code */
	printf ("%02x => %08x = %+11.6f (spacing = %+11.6f)\n",
											i, *(int*) &f, f, prev-f);
	
	prev = f;
	}

  return 0;
}
