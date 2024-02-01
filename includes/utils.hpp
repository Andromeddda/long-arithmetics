using namespace std;

#define TERMINATE(message) 				\
	std::cout << message << std::endl; 	\
	exit(1);

#define VERIFY_CONTRACT(contract, message) 			\
	if (!(contract)) { 								\
		std::cout << message << std::endl; 			\
		exit(1); 									\
	}

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define SET_COLOR_CYAN "\033[1;36m"
#define RESET_COLOR "\033[0m"

#define DEBUG_BREAKPOINT \
	std::cout << SET_COLOR_CYAN << "[===DEBUG===]: [" << __FUNCTION__ << \
	"] on line " << __LINE__ << RESET_COLOR << endl; 

#define DEBUG_M(message) \
	std::cout << SET_COLOR_CYAN << "[===DEBUG===]: [" << __FUNCTION__ << \
	"] on line " << __LINE__ << "|" << message << RESET_COLOR << endl;
