/*
	Nicholas Barrs (nbarrs)
	CPSC 2310-002
	Program 2
	22 Feb 2016

	Binary Multiplication--Prints the individual steps for multiplying
	two 8-bit binary numbers "by hand"
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

struct variables {
	int multiplicand, multiplier, carry, acc, mq, mdr, solution;
};

/* converts a given integer to a given bit-length binary number
	and returns it as a string */
string prt_bin(int value, int length) {
	string binary;

	for (int i = (length-1); i>= 0; i--) 
		if ((value>>i) & 1) binary.push_back('1');
		else binary.push_back('0');

	return binary;
}

/* prints a series of 50 '-' characters to divide steps */
void prt_line(void) {
	for (int i=0; i<50; i++) putchar('-');
	putchar('\n');
	return;
}

/* prompts the user to input the multiplicand and multiplier
	and stores them in corresponding variables */
bool read_input(variables *var) {
	cout << "Enter two integers between 0-255 to multiply:\n";
	cin >> var->multiplicand >> var->multiplier;
	if (var->multiplicand<0 || var->multiplicand>255
		 ||var->multiplier<0 || var->multiplier>255) {
		cout << "Error: invalid value(s)!\n";
		return false;
	}
	return true;
}

/* prints the initial values of all of the program's variables */
void initialize(variables *var) {
	prt_line();
	cout << "multiplicand: " << var->multiplicand << endl;
	cout << "multiplier: " << var->multiplier << endl << endl;
	
	var->carry = 0;
	var->acc = 0;
	cout << "c and acc set to 0" << endl;
	
	var->mq = var->multiplier;
	cout << "mq set to multiplier    = " << var->multiplier << " decimal ";
	cout << "and " << prt_bin(var->multiplier, 8) << " binary" << endl;
	
	var->mdr = var->multiplicand;
	cout << "mdr set to multiplicand = " << var->multiplicand << " decimal ";
	cout << "and " << prt_bin(var->multiplicand, 8) << " binary" << endl;
	prt_line();
	return;
}

/* prints first line of each step of the multiplication process in the form:
	step #:  carry  accumulator  mq */
void prt_step_first_line(int step, variables *var) {
	cout << "step " << step+1 << ":   ";
	cout << var->carry << " " << prt_bin(var->acc,8) << " ";
	cout << prt_bin(var->mq,8) << endl;
}

/* adds the values in the accumulator and mdr and stores the result in acc,
	and prints the visual representation of such process */
void add(variables *var) {
	cout << "        +   " << prt_bin(var->mdr,8) << "        ^ ";
	cout << "add based on lsb=1" << endl;
	cout << "          ----------" << endl;
	var->acc = var->acc + var->multiplicand;
	if (var->acc > 255) var->carry = 1; // set carry to 1 if new acc is > 255
}

/*	doesn't change accumulator value but still prints visual representation
	of the process */
void dont_add(void) {
	cout << "        +   " << prt_bin(0,8) << "        ^ ";
	cout << "no add based on lsb=0" << endl;
	cout << "          ----------" << endl;
}

/* shifts value of carry:accumulator:mq by 1 bit to the right */
void shift_right(variables *var) {
	var->mq = var->mq>>1;
	if (prt_bin(var->acc,8)[7] == '1') var->mq += 128;

	var->acc = var->acc>>1;
	var->carry = 0;
}

/* executes, and prints the visual representation of, the rest of each step
	in the multiplication process (result of addition, shift, and result of
	shift) */
void rest_of_step(variables *var) {
	cout << "          " << var->carry << " " << prt_bin(var->acc,8) << " ";
	cout << prt_bin(var->mq,8) <<endl;
	cout << "       >>                    shift right" << endl;
	shift_right(var);
	cout << "          " << var->carry << " " << prt_bin(var->acc,8) << " ";
	cout << prt_bin(var->mq,8) << endl;
	prt_line();
}

/* high-level and abstract execution of the multiplication process */
void evaluate_and_print(int step, variables *var) {
	prt_step_first_line(step, var);
	if (prt_bin(var->mq,8)[7] == '1') add(var);
	else dont_add();
	rest_of_step(var);	
	return;
}

/* converts a string representation of a binary number to an integer */
int binary_to_decimal(string binary) {
	int sum = 0;
	for (int i=binary.length(); i>=0; i--) {
		if (binary[i-1] == '1')
			sum += pow(2.0, binary.length() - i); 
	}
	return sum;
}

/* "check"s the result of the multiplication process and prints the visual
	representation of the check */
void check_result(variables *var) {
	string bin_solution = prt_bin(var->acc, 8) + prt_bin(var->mq, 8);
	var->solution = binary_to_decimal(bin_solution);	
	cout << "check:                 binary   decimal" << endl;
	cout << "                     " << prt_bin(var->multiplicand,8);
	printf("%10i\n", var->multiplicand);
	cout << "           x         " << prt_bin(var->multiplier,8);
	printf("  x%7i\n", var->multiplier);
	cout << "             ----------------    ------" << endl;
	cout << "             " << bin_solution;
	printf("%10i\n", var->solution);
}

/* abstract representation of entire program */
int main (void) {
	struct variables var;	
	if (!read_input(&var)) return 0;
	initialize(&var);	
	for (int i=0; i<8; i++) evaluate_and_print(i, &var);
	check_result(&var);

	return 0;
}

