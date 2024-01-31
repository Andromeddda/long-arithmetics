using namespace std;

#include <string>
#include "long-number.hpp"
#include "utils.hpp"

// // // // // // //
//  Constructors  //
// // // // // // //

// Construct 0.0
LongNumber::LongNumber() {
	exponent = 1;
	sign = 1;
	digits = vector<int>(1, 0);
}

// Copy constructor
LongNumber::LongNumber(LongNumber& other) {
	exponent = other.get_exponent();
	sign = other.get_sign();
	digits = vector<int>(other.get_digits());
}

// Construct LongNumber from string literal
LongNumber::LongNumber(const string& literal) {
	int index = 0;

	// check if there is a sign
	if (literal[index] == '-') {
		sign = -1;
		index++;
	}
	else {
		sign = 1;
	}

	// Count the number of points in case of incorrect form
	int count_points = 0;

	// significant == false if current digit is a leading zero
	bool significant = false;

	exponent = 0;
	int length = literal.length();

	while (index < length) {

		// Handle the case of point
		if (literal[index] == '.') {
			VERIFY_CONTRACT(count_points == 0, 
				"LongNumber(const string): incorrect form of number, more than one point");
			count_points++;
			index++;
			continue;
		}

		// Handle the case of non-digit (throw exception)
		VERIFY_CONTRACT(isdigit(literal[index]), 
			"LongNumber(const string): incorrect form of number, unexpected character");

		// Handle the case of digit
		// Check if current digit is significant
		significant |= (literal[index] != '0');

		// push every significant digit
		if (significant) {
			digits.push_back(literal[index] - '0');
			// every significant digit before point increases the exponent
			if (count_points == 0) exponent++; 
		}
		else {
			// every insignificant digit after point decreases the exponent
			if (count_points > 0) exponent--;
		}
		index++;
	}

	// Remove zeros from the back
	index = digits.size() - 1;
	while(digits[index] == 0) {
		digits.pop_back();
		index--;
	}

}

// Construct LongNumber from floating literal
// Delegate constructor (works for C++11 and >)
LongNumber::LongNumber(long double number) : LongNumber(std::to_string(number)) {}

// // // // // //
//  Operators  //
// // // // // //

// Return true if number != 0
LongNumber::operator bool() const {
	return (exponent != 1) || (digits[0] != 0);
}

LongNumber operator""_ln(long double number) { 
	return LongNumber(number);
}

