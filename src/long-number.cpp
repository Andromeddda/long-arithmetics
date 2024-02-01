using namespace std;

#include <string>
#include "long-number.hpp"
#include "utils.hpp"

// // // // // // // // // // 
//  Utils for long numbers //
// // // // // // // // // //

void long_print(LongNumber& x) {
	if (x.get_sign() == -1) {
		std::cout << '-';
	}

	int exp = x.get_exponent(), size = x.get_digits().size();
	if (exp > 0) {
		for (int i = 0; i < size; i++) {
			if (i == exp) std::cout << '.';
			std::cout << x.get_digits()[i];
		}
	}
	else {
		std::cout << "0.";
		for (int i = 0; i > exp; i--) {
			std::cout << 0;
		}
		for (int i = -exp; i < size; i++) std::cout << x.get_digits()[i];
	}
}


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

// User-defined floating-point literal
LongNumber operator""_ln(long double number) { 
	return LongNumber(number);
}

// // // // // //
//  Operators  //
// // // // // //

// Return true if number != 0
LongNumber::operator bool() const {
	return (exponent != 1) || (digits[0] != 0);
}

// Unary minus 
LongNumber LongNumber::operator- () {
    LongNumber result;
    result.sign = -sign;
    result.exponent = exponent;
    result.digits = vector<int>(digits);
    return result;
}

LongNumber LongNumber::operator+ (const LongNumber& other) {
    // Case: number + 0.0
    if(!(*this)) return LongNumber(other);
    if(!other) return LongNumber(*this);
    
    // Case: different signs
    if (sign != other.sign) {
        if (sign == -1) {
            // Case: negative + positive (call operator-)
            return other - (-(*this));
        }
        else {
            // Case: positive + negative (call operator-)
            return *this - (-other);
        }
    }
    
    // Case: similar signs

    // If we have numbers like 1234e6 and 5678e-3
    // We should bring them into form 123400.0000000 and 000000.0005678

    // Copy exponents
    int ex1 = exponent;
    int ex2 = other.exponent;
    int res_ex = MAX(ex1, ex2);

    // Copy digits
    vector<int> d1 = vector<int>(digits);
    vector<int> d2 = vector<int>(other.digits);

    // Insert zeros in the front 
    //		(with previous example we'll had [1,2,3,4] and [0, ... ,0,5,6,7,8]
    if (ex1 < res_ex) {
    	d1.insert(d1.begin(), (size_t)(res_ex - ex1), 0);
    	ex1 = res_ex;
    }
    if (ex2 < res_ex) {
    	d2.insert(d2.begin(), (size_t)(res_ex - ex2), 0);
    	ex2 = res_ex;
    }

    // Find new size to insert zeros in the back
    size_t size = MAX(d1.size(), d2.size());

    // Insert zeros in the back
    if (d1.size() < size)
    	d1.insert(d1.end(), size - d1.size(), 0);
    if (d2.size() < size)
    	d2.insert(d2.end(), size - d2.size(), 0);

    LongNumber result; // Create new number
    result.sign = sign; // Because operands has similar signs in this case
    result.digits = vector<int>(1 + size, 0); // Because of probable overflow

    // Go from the back and add
    int overflow = 0, sum = 0;
    for (int i = size - 1; i >= 0; i--) {
    	sum = d1[i] + d2[i] + overflow;
    	result.digits[i+1] = sum % 10;
    	overflow = sum / 10;
    }

    // Insert or pop the first digit
    if (overflow != 0) {
    	result.digits[0] = overflow;
    	result.exponent = res_ex + 1;
    }
    else {
    	result.digits.erase(result.digits.begin());
    	result.exponent = res_ex;
    }

    // Remove zeros from the back
	int index = result.digits.size() - 1;
	while(digits[index] == 0) {
		digits.pop_back();
		index--;
	}

	return result;
}


