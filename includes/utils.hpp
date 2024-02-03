using namespace std;

#include <iostream>
#include <ctime>

// // // // // // //
//  SAFETY UTILS  //
// // // // // // //

#define TERMINATE(message) 				\
	std::cout << message << std::endl; 	\
	exit(1);

#define VERIFY_CONTRACT(contract, message) 			\
	if (!(contract)) { 								\
		std::cout << message << std::endl; 			\
		exit(1); 									\
	}

// // // // // //
//  CODE UTILS //
// // // // // //

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// // // // // //
// DEBUG UTILS //
// // // // // //

#define SET_COLOR_CYAN "\033[1;36m"
#define RESET_COLOR "\033[0m"

#define DEBUG_B \
	std::cout << SET_COLOR_CYAN << "[===DEBUG===]: [" << __FUNCTION__ << \
	"] on line " << __LINE__ << RESET_COLOR << endl; 

#define DEBUG_M(message) \
	std::cout << SET_COLOR_CYAN << "[===DEBUG===]: [" << __FUNCTION__ << \
	"] on line " << __LINE__ << " | " << message << RESET_COLOR << endl;

#define DEBUG_EXEC(func, ...) 																					\
	std::cout << SET_COLOR_CYAN << "[===DEBUG===]: [" << __FUNCTION__ << "] on line " << __LINE__ << " | "; 	\
	func(__VA_ARGS__); 																							\
	std::cout << RESET_COLOR << std::endl;

// // // // // //
// TIME UTILS  //
// // // // // //

#define TIMING(msg, func, ...)																\
	{ 																						\
	clock_t start = clock(); 																\
	func(__VA_ARGS__); 																		\
	clock_t end = clock();																	\
	std::cout << msg << (double)(end - start) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;	\
	}

#define KARATSUBA_MIN_LEN 300
