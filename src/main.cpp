using namespace std;

#include <iostream>
#include <string>
#include "long-number.hpp"
#include "utils.hpp"

int main(void) {

	LongNumber x = LongNumber(3.1415);
	// LongNumber x = LongNumber("-0.00314150000");

	cout << "sign:" << x.get_sign() << endl;
	cout << "exponent:" << x.get_exponent() << endl;
	cout << "size:" << x.get_digits().size() << endl;

	for (int i = 0; i < (int)x.get_digits().size(); i++) {
		cout << x.get_digits()[i];
	}


	return 0;
}