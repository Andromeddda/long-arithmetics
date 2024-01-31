using namespace std;

#define TERMINATE(message) 		\
	cout << message << endl; 	\
	exit(1);

#define VERIFY_CONTRACT(contract, message) 	\
	if (!(contract)) { 						\
		cout << message << endl; 			\
		exit(1); 							\
	}
