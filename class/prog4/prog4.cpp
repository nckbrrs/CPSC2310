/*

	Nicholas Barrs (nbarrs)
	CPSC 2310-002
	Program Assignment 4
	April 14, 2015

	prog4.cpp takes in two integers between 0-255 from the user and
	1) prints the values of the integers' corresponding 8-bit floating point vals
	2) shows the steps required in adding the two floating point values

*/

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;

// floating point structure skeleton
struct fp {
	int input;
	int sign, orig_exp, int_fraction;
	int hidden_bit, biased_exp, gr;
	float dec_signif, final_value;
};

// function prototypes
string prt_bin(int value, int length);
void read_input(fp *f1, fp *f2);
void extract_fields(fp *f);
void apply_bias(fp *f);
void compute_signif(fp *f);
void compute_final_value(fp *f);
void copy_values(fp *f1, fp *f2);
void print_internal_rep(fp *f, char v, int version);
void print_intro(fp *f1, fp *f2, int version);
void print_conversions(fp *f1, fp *f2);
void shift_right(fp *f);
void shift_left(fp *f);
void negate_float(fp *f);
void add_signifs(fp *f_1, fp *f_2, fp *r);
int perform_addition(fp *f1, fp *f2, fp *result);
void print_addition_results(fp *f1, fp *f2, fp *result);

int main(void) {
	// instantiate floating point structures
	fp first, second, addend_1, addend_2, sum;
	
	// read user input
	read_input(&first, &second);

	// extract bit fields from user input
	extract_fields(&first);
	extract_fields(&second);

	// apply bias to exponents if necessary
	apply_bias(&first);
	apply_bias(&second);

	// compute decimal significand (1.DDDD, where D is a digit 0-9) of inputs
	compute_signif(&first);
	compute_signif(&second);

	// compute final decimal value of input
	compute_final_value(&first);
	compute_final_value(&second);
	
	// print initial values of input, and then print final converted values
	print_intro(&first, &second, 0);
	print_conversions(&first, &second);

	// copy inputted values into new float structures to be used for adding,
	// so initial inputted values are not modified
	copy_values(&first, &addend_1);
	copy_values(&second, &addend_2);

	// print initial values of input
	print_intro(&addend_1, &addend_2, 1);

	// perform addition. if successful, print summary of results
	if (perform_addition(&addend_1, &addend_2, &sum))
		print_addition_results(&first, &second, &sum);
}

/*
	prt_bin:
	converts an integer value to a binary string of specified
	bit-length, and returns the binary string 
*/
string prt_bin(int value, int length) {
	string binary;
	for (int i = (length-1); i >= 0; i--)
		if ((value>>i) & 1) binary.push_back('1');
		else binary.push_back('0');

	return binary;
}

/*
	read_input:
	prompts user for two integers and stores those values in the two
	floating point parameters' respective input fields. if either inputted
	integer value is not between 0-255, it continues to prompt the user for
	values until both are within the correct range.
*/
void read_input(fp *f1, fp *f2) {
	cout << "Enter two integers between 0 and 255:\n";
	scanf("%d %d", &f1->input, &f2->input);

	while (f1->input<0 || f1->input>255 || f2->input<0 || f2->input>255) {
		cout << "Error! One or both of your integers are not between 0-255.";
		cout << "Try again.\nEnter two integers between 0 and 255:\n";
		scanf("%d %d", &f1->input, &f2->input);
	}
}

/*
	extract_fields:
	extracts the sign, exponent, and fraction bit fields from the inputted
	integer using bit masks, and assigns the fields to their respective values
	in the floating point structure that was sent as a parameter
*/
void extract_fields(fp *f) {
	f->int_fraction = (f->input & 15);
	f->orig_exp = ((f->input >> 4) & 7);
	f->sign = ((f->input >> 7) & 1);
	f->gr = 0;
}

/*
	apply_bias:
	applies a bias of -4 to the floating point structure's exponent and sets
	its hidden bit to 1 if its initial exponent value is not 0. 
	if its initial exponent value is 0, set its biased exponent value 
	and hidden bit to 0 as well.
*/
void apply_bias(fp *f) {
	if (f->orig_exp != 0) {
		f->biased_exp = f->orig_exp - 4;
		f->hidden_bit = 1;
	}
	else {
		f->biased_exp = 0;
		f->hidden_bit = 0;
	}
}

/*
	compute_signif:
	computes the decimal significand (1.DDDD) of the floating point based on 
	its fraction and hidden bit fields
*/
void compute_signif(fp *f) {
	f->dec_signif = 0;

	// add appropriate negative powers of 2 to the floating point structure's
	// decimal significand by checking which bits are set in the fraction field
	if (f->orig_exp != 0) {
		if (f->int_fraction & 1) f->dec_signif += pow(2, -4);
		if (f->int_fraction & 2) f->dec_signif += pow(2, -3);
		if (f->int_fraction & 4) f->dec_signif += pow(2, -2);
		if (f->int_fraction & 8) f->dec_signif += pow(2, -1);
		f->dec_signif += (f->hidden_bit & 3);
	}
}

/*
	compute_final-value:
	computes the final floating point value of the inputted integer by
	multipling its decimal significand by 2^(biased exponent)--unless
	the initial exponent was 0, in which case the final floating point value
	is 0. this function also applies the negative if necessary.
*/
void compute_final_value(fp *f) {
	if (f->orig_exp == 0) f->final_value = 0;
	else f->final_value = f->dec_signif * pow(2, f->biased_exp);

	if (f->sign == 1) {
		f->final_value *= -1;
		f->dec_signif *= -1;
	}
}

/*
	copy_values:
	copies values from one floating point structure into another
*/
void copy_values(fp *f1, fp *f2) {
	f2->input = f1->input;
	f2->sign = f1->sign;
	f2->hidden_bit = f1->hidden_bit;
	f2->orig_exp = f1->orig_exp;
	f2->biased_exp = f1->biased_exp;
	f2->int_fraction = f1->int_fraction;
	f2->gr = f1->gr;
	f2->dec_signif = f1->dec_signif;
	f2->final_value = f1->final_value;
}

/*
	print_internal_rep:
	prints the internal representation of a floating point, which is
	its hidden bit, fraction, and biased exponent fields. if
	this function is called with 1 as the "version" parameter (which will happen
	when called within the addition process), it also prints the guard and round
	bit field.
*/
void print_internal_rep(fp *f, char c, int version) {
	cout << "  internal rep of ";
	switch (c) {
		case '1':
			cout << "first value:    " << prt_bin(f->hidden_bit, 1);
			break;
		case '2':
			cout << "second value:   " << prt_bin(f->hidden_bit, 1);
			break;
		default:
			cout << "sum:           " << prt_bin(f->hidden_bit, 2);
			break;
	}

	cout << "." << prt_bin(f->int_fraction, 4);
	if (version == 1) cout << " " << prt_bin(f->gr, 2);
	cout << " x 2^(" << f->biased_exp << ")\n";
}

/*
	print_intro:
	prints the initial values in the forms of integer, binary, 
	and internal representation. also indicates the hidden bit and fraction
	fields.
*/
void print_intro(fp *f1, fp *f2, int version) {
	cout << "----\n\n";
	cout << "  first value:  " << f1->input << endl;
	cout << "  second value: " << f2->input << endl << endl;

	cout << "  encoding of first value:        " << prt_bin(f1->input,8) << endl;
	cout << "  encoding of second value:       " << prt_bin(f2->input,8) << endl;
	cout << endl;

	print_internal_rep(f1, '1', version);
	print_internal_rep(f2, '2', version);

	cout << "  hidden bit----------------------^ ffff";
	if (version == 1) cout << " gr";
	cout << "\n  4-bit fraction--------------------^^^^" << endl << endl;
}


/*
	print_conversions:
	prints the two values as a conversion from their decimal significands to
	their final floating point values
*/
void print_conversions(fp *f1, fp *f2) {
	cout << "  first value is:  ";
	if (f1->sign == 0) cout << "+";
	printf("%.4f x 2^(%i) = %f\n", 
		f1->dec_signif, f1->biased_exp, f1->final_value);

	cout << "  second value is: ";
	if (f2->sign == 0) cout << "+";
	printf("%.4f x 2^(%i) = %f\n\n",
		f2->dec_signif, f2->biased_exp, f2->final_value);
}

/*
	shift_right:
	shifts the hidden bit, fraction, and guard and round bits of a floating
	point number as a unit to the right 1 place, and adjusts exponent
*/
void shift_right(fp *f) {
	f->gr = (((f->gr & 3) >> 1) & 3);
	if (f->int_fraction & 1) f->gr += 2; 
	f->int_fraction = (((f->int_fraction & 15) >> 1) & 15);

	if (f->hidden_bit & 1) f->int_fraction = f->int_fraction + 8;

	f->hidden_bit = (((f->hidden_bit & 3) >> 1) & 3);

	f->biased_exp++;
}

/*
	shift_left:
	shifts the hidden bit, fraction, and guard and round bits of a floating
	point number as a unit to the left 1 place, and adjusts exponent
*/
void shift_left(fp *f) {
	f->hidden_bit = (((f->hidden_bit & 3) << 1) & 3);
	if (f->int_fraction & 8) f->hidden_bit++;

	f->int_fraction = (((f->int_fraction & 15) << 1) & 15);
	if (f->gr & 2) f->int_fraction++;

	f->gr = (((f->gr & 3) << 1) & 3);
	
	f->biased_exp--;
}

/*
	negate_float:
	converts a floating point value's hidden bit, fraction, and guard and round
	bits to its 2's complement representation
*/
void negate_float(fp *f) {
	// take the 2's complement of the hidden bit, fraction, and guard and round
	// bit fields of the floating point structure by XOR-ing them with the
	// largest value representable by their respective bit-field sizes,
	// and then adding 1 to final result, adjusting the fraction and hidden bit
	// fields if necessary
	f->hidden_bit = ((f->hidden_bit & 3) ^ 3);
	f->int_fraction = ((f->int_fraction & 15) ^ 15);
	f->gr = ((f->gr & 3) ^ 3);

	f->gr++;
	if (f->gr > 3) f->int_fraction++;
	if (f->int_fraction > 15) f->hidden_bit++;
}

/*
	add_signifs:
	adds the significands (hidden bit, fraction, and guard and round fields) of
	two floating point structures (f_1 and f_2) and stores the 
	corresponding results into another floating point structure (r)
*/
void add_signifs(fp *f_1, fp *f_2, fp *r) {
	// initialize sum's values
	r->gr = 0;
	r->int_fraction = 0;
	r->hidden_bit = 0;
	r->biased_exp = f_1->biased_exp;

	// compute sum's guard and round bit field
	r->gr = (f_1->gr & 3) + (f_2->gr & 3);
	if (r->gr > 3) r->int_fraction++;

	// compute sum's fraction bit field
	r->int_fraction += ((f_1->int_fraction & 15) + (f_2->int_fraction & 15));
	if (r->int_fraction > 15) r->hidden_bit++;

	// compute sum's hidden bit field
	r->hidden_bit += ((f_1->hidden_bit & 3) + (f_2->hidden_bit & 3));
}

/*
	perform_addition:
	performs the following steps of floating point addition:
		* swap operands until exp of first >= exp of second
		* shift significand of second operand until exponents match
		* take 2's complement of any operand with sign bit set
		* add significands
		* take 2's complement of sum if it is negative, and set sign bit
		* normalize if sum is too large or small by shifting
		* round sum
		* normalize if sum is too large
		* check range of sum's exponent and exit if it is too large or small
		* add bias to sum's exponent
		* construct sum's final values
*/
int perform_addition(fp *f1, fp *f2, fp *result) {
	cout << "  addition of the values:\n\n";

	// if either addend = 0, sum is simply the other addend, and thus
	// there is no need to complete the addition process.
	if (f1->final_value == 0) {
		copy_values(f2, result);
		cout << "  f1 is 0, so sum = f2. no need to add.\n\n";
		return 1;
	}

	if (f2->final_value == 0) {
		copy_values(f1, result);
		cout << "  f2 is 0, so sum = f1. no need to add.\n\n";
		return 1;
	}

	// swap operands if necessary so that f1->exp >= f2->exp
	if (f2->biased_exp > f1->biased_exp) {
		fp *temp = f2;
		f2 = f1;
		f1 = temp;
		cout << "  operands have been swapped\n";
		print_internal_rep(f1, '1', 1);
		print_internal_rep(f2, '2', 1);
	}

	// right shift significand of second operand until exponents match
	while (f1->biased_exp != f2->biased_exp) {
		shift_right(f2);
		cout << "  second operand shifted to equalize exponents\n";
		print_internal_rep(f2, '2', 1);
	}

	// take 2's complement of any operand with sign bit set
	if (f1->sign == 1) {
		negate_float(f1);
		cout << "  first operand negated\n";
		print_internal_rep(f1, '1', 1);
	}
	if (f2->sign == 1) {
		negate_float(f2);
		cout << "  second operand negated\n";
		print_internal_rep(f2, '2', 1);
	}

	cout << "  addition takes place\n";

	// add significands
	print_internal_rep(f1, '1', 1);
	print_internal_rep(f2, '2', 1);
	add_signifs(f1, f2, result);
	print_internal_rep(result, '3', 1);

	// negate sum if necessary
	if ((f1->final_value + f2->final_value) < 0) {
		result->sign = 1;
		negate_float(result);
		cout << "  sum negated\n";
		print_internal_rep(result, '3', 1);
	}
	else result->sign = 0;

	// normalize if the sum is too large or small
	while ((result->hidden_bit & 3) > 1) {
		shift_right(result);
		cout << "  sum normalized\n";
		print_internal_rep(result, '3', 1);
	}
	while ((result->hidden_bit & 3) < 1) {
		shift_left(result);
		cout << "  sum normalized\n";
		print_internal_rep(result, '3', 1);
	}

	// round appropriately
	if (((result->gr & 3) > 2) || 
	(((result->gr & 3) == 2) && (result->int_fraction & 1))) {
		result->int_fraction++;
		if ((result->int_fraction & 15) > 15) result->hidden_bit++;
		cout << "  sum rounded\n";
		print_internal_rep(result, '3', 1);
	}

	while ((result->hidden_bit & 3) > 1) {
		shift_right(result);
		cout << "  sum normalized\n";
		print_internal_rep(result, '3', 1);
	}

	cout << "  hidden bit----------------------^ ffff gr";
	cout << "\n  4-bit fraction--------------------^^^^\n\n";

	// range check the result exponent
	if (result->biased_exp > 3 || result->biased_exp < -3) {
		cout << "  Error: sum's exponent is too large/small to be represented.\n";
		cout << "  Addition terminated.\n\n";
		cout << "----\n";
		return 0;
	}

	// add bias to result exponent
	if (f1->orig_exp != 0 && f2->orig_exp != 0)
	result->orig_exp = result->biased_exp + 4;

	// compute result values
	compute_signif(result);
	compute_final_value(result);

	return 1;
}

/*
	print_addition_results:
	prints the binary encoding of the sum as well as a summary of the addition
	process, including the decimal-significand-to-float-value conversions of
	the initial inputted values as well as the decimal-significand-to-float-value
	of the sum.
*/
void print_addition_results(fp *f1, fp *f2, fp *result) {
	// print binary encoding of sum
	cout << "  encoding of sum:                ";
	cout << prt_bin(result->sign, 1);
	cout << prt_bin(result->orig_exp, 3);
	cout << prt_bin((result->int_fraction & 15), 4) << endl << endl;

	// print summary (conversions of initial values and conversions of sum)
	cout << "                 ";
	printf("%.5f", f1->dec_signif); 
	cout << "x 2^(";
	if (f1->biased_exp >= 0) cout << "+";
	cout << f1->biased_exp << ")";
	printf(" = %.7f\n", f1->final_value);

	cout << "        added to ";
	printf("%.5f", f2->dec_signif); 
	cout << "x 2^(";
	if (f2->biased_exp >= 0) cout << "+";
	cout << f2->biased_exp << ")";
	printf(" = %.7f\n", f2->final_value);

	cout << "          equals ";
	printf("%.5f", result->dec_signif); 
	cout << "x 2^(";
	if (result->biased_exp >= 0) cout << "+";
	cout << result->biased_exp << ")";
	printf(" = %.7f\n\n", result->final_value);
	cout << "----\n\n";

}
