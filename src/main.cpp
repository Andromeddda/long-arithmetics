using namespace std;

#include <iostream>
#include <string>
#include "long-number.hpp"
#include "utils.hpp"

int main(void) {
	LongNumber x = 123400.0_ln;
	LongNumber y = 0.005678_ln;
	
	long_print(x);
	long_print(y);
	LongNumber w = x - y;

	long_print(w);

	return 0;
}