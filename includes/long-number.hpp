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
	bool operator != (const LongNumber& other);

	// Basic binary operators
	LongNumber operator+ (const LongNumber& other);
	LongNumber operator- (const LongNumber& other);

	// Karatsuba multiplication (recursive algorithm) complexity = O(n ^ 1.585)
	LongNumber operator*(const LongNumber& other);

	// LongNumber operator/(const LongNumber& left, LongNumber& right);
};

void vector_print(vector<int>& vec);

// User-defined floating-point literal
LongNumber operator""_ln(long double number);

// Print the long number to the console
void long_print(LongNumber& x);

// // // // // // // //
//  Karatsuba utils  //
// // // // // // // //

// Recursive multiplication of two vectors
vector<int> Karatsuba(vector<int>& left, vector<int>& right);

// Multiply two vector<int> with complixity O(n^2)
vector<int> naive_multiplication(vector<int>& left, vector<int>& right);



// overload addition of vectors
vector<int> operator+ (const vector<int>& x, const vector<int>& y);

// overload subtraction of vectors
vector<int> operator- (const vector<int>& x, const vector<int>& y);