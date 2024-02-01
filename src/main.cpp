using namespace std;

#include <iostream>
#include <string>
#include "long-number.hpp"
#include "utils.hpp"

int main(void) {
	LongNumber x = 3.1415_ln;
	LongNumber y = 2000.0000007_ln;
	
	LongNumber z = x + y;
	long_print(z);

	return 0;
}