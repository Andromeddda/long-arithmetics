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
		for (int i = 0; i < size; i++) std::cout << x.get_digits()[i];
	}
	std::cout << std::endl;
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

// // // // // // // //
//  Logic Operators  //
// // // // // // // //

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

// Comparison operators

bool LongNumber::operator== (const LongNumber& other) {
	return (sign == other.sign) && (exponent == other.exponent) && (digits == other.digits);
}

bool LongNumber::operator> (const LongNumber& other) {
	// In case of different signs
	if (sign != other.sign) return sign > other.sign;
	// In case of different exponents
	if (exponent != other.exponent) return (exponent > other.exponent) ^ (sign == -1);

	// Exponents and signs are equal

	// Copy vectors
	vector<int> d1 = vector<int>(digits);
	vector<int> d2 = vector<int>(other.digits);

	// Push zeros to balance sizes
	size_t size = MAX(d1.size(), d2.size());
	if (d1.size() < size)
		d1.insert(d1.end(), size - d1.size(), 0);
	if (d2.size() < size)
		d2.insert(d2.end(), size - d2.size(), 0);

	// Run through vectors and compare
	for (unsigned int i = 0; i < size; i++) {
		if (d1[i] != d2[i]) {
			return (d1[i] > d2[i]) ^ (sign == -1);
		}
	}
	return false;
}

bool LongNumber::operator>= (const LongNumber& other) {
	return (*this == other) || (*this > other);
}

bool LongNumber::operator< (const LongNumber& other) {
	return !(*this >= other);
}

bool LongNumber::operator<= (const LongNumber& other) {
	return !(*this > other);
}

// // // // // // // //
// Numeric Operators //
// // // // // // // //

LongNumber LongNumber::operator+ (const LongNumber& other) {
	// SPECIAL CASES
	// Case: x + (-x) to return correct 0.0 with sign == 1
	if (*this == (LongNumber)(-other)) return LongNumber();

    // Case: number + 0.0
    if(!(*this)) return LongNumber(other);
    if(!other) return LongNumber(*this);
    
    // Case: different signs (call operator-)
    if (sign != other.sign) {
        if (sign == -1) {
            // negative + positive 
            return other - (-(*this));
        }
        else {
            // positive + negative
            return *this - (LongNumber)(-other);
        }
    }
    
    // MAIN CASE

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
	while(result.digits[index] == 0) {
		result.digits.pop_back();
		index--;
	}

	return result;
}

LongNumber LongNumber::operator- (const LongNumber& other) {
	// SPECIAL CASES
	// Case: x - x to return correct 0.0 with sign == 1
	if (*this == other) return LongNumber();

	// Case: different signs (call operator+)
	if (sign != other.sign) return *this + (LongNumber)(-other);

	// Case: both negative 
	if ((sign == -1) && (other.sign == -1)) return (-other) - (-(*this));

	// MAIN CASE
	bool compare = *this > other;
	// Exponents of biggest and smallest numbers
	int ex1 = compare ? exponent : other.exponent;
	int ex2 = compare ? other.exponent : exponent;
	int res_ex = MAX(ex1, ex2);

	// Digits of biggest and smallest numbers
	vector<int> d1 = vector<int>(compare ? digits : other.digits);
	vector<int> d2 = vector<int>(compare ? other.digits : digits);

	// BALANCE ZEROS
	// Insert zeros in the front 
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

    // Create new number
    LongNumber result;
    result.sign = compare ? 1 : -1;
    result.digits = vector<int>(size, 0);

    // Run and subtract
    int loan = 0; 
    for (int i = size - 1; i >= 0; i--) {
    	if (d1[i] - loan < d2[i]) {
    		// Need to take extra 10 from next digit
    		result.digits[i] = 10 + d1[i] - loan - d2[i];
    		loan = 1;
    	}
    	else {
    		result.digits[i] = d1[i] - loan - d2[i];
    		loan = 0;
    	}
    }

    // Remove first digit if it is 0
    if (result.digits[0] == 0) {
    	result.digits.erase(result.digits.begin());
    	result.exponent = res_ex - 1;
    }
    else {
    	result.exponent = res_ex;
    }

    // Remove zeros from the back
	int index = result.digits.size() - 1;
	while(result.digits[index] == 0) {
		result.digits.pop_back();
		index--;
	}

	return result;
}


