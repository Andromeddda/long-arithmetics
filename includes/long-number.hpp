using namespace std;

#include <iostream>
#include <vector>

class LongNumber {
	// exponent is the number of digits before the point
	int exponent;

	// Example: 1234.5678 is represented as 0.12345678e4
	std::vector<int> digits;

	int sign;

public:
	// // // // // 
	// 	Getters //
	// // // // // 

	vector<int> get_digits() { return digits; }
	int get_exponent() { return exponent; }
	int get_sign() { return sign; }

	// // // // // // //
	// 	Constructors  //
	// // // // // // //

	// Construct 0.0
	LongNumber();

	// Copy constructor
	LongNumber(LongNumber& other);

	// Construct LongNumber from double
	LongNumber(double literal);

	// Construct LongNumber from string literal
	LongNumber(const string& literal);


	// LongNumber operator+(const LongNumber& left, LongNumber& right);
	// LongNumber operator-(const LongNumber& left, LongNumber& right);
	// LongNumber operator*(const LongNumber& left, LongNumber& right);
	// LongNumber operator/(const LongNumber& left, LongNumber& right);
};