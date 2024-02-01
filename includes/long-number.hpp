using namespace std;

#include <iostream>
#include <vector>

#pragma once

class LongNumber {
	// Example: 1234.5678 is represented as 0.12345678e4
	std::vector<int> digits;

	// exponent is the number of digits before the point
	int exponent;


	int sign;

public:
	// // // // // 
	// Getters  //
	// // // // // 

	vector<int> get_digits() { return digits; }
	int get_exponent() { return exponent; }
	int get_sign() { return sign; }

	// // // // // // //
	//  Constructors  //
	// // // // // // //

	// Construct 0.0
	LongNumber();

	// Copy constructor
	LongNumber(LongNumber& other);

	// Construct LongNumber from double
	LongNumber(long double literal);

	// Construct LongNumber from string literal
	LongNumber(const string& literal);

	// // // // // //
	//  Operators  //
	// // // // // //

	// Return true if number != 0
	operator bool() const;

	// Unary minus
	LongNumber operator- ();

	// Comparison operators
	bool operator== (const LongNumber& other);
	bool operator> (const LongNumber& other);
	bool operator>= (const LongNumber& other);
	bool operator< (const LongNumber& other);
	bool operator<= (const LongNumber& other);

	// Basic binary operators
	LongNumber operator+ (const LongNumber& other);
	LongNumber operator- (const LongNumber& other);
	// LongNumber operator*(const LongNumber& left, LongNumber& right);
	// LongNumber operator/(const LongNumber& left, LongNumber& right);
};

// User-defined floating-point literal
LongNumber operator""_ln(long double number);

void long_print(LongNumber& x);