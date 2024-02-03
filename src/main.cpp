using namespace std;

#include <iostream>
#include <string>
#include "long-number.hpp"
#include "utils.hpp"
#include <ctime>

int main(void) {
	
	int N;
	cin >> N;

	vector<int> a = vector<int>(N, 9);
	vector<int> b = vector<int>(N, 8);

	TIMING("Naive: ", naive_multiplication, a, b)
	TIMING("Karatsuba: ", Karatsuba, a, b)

	return 0;
}