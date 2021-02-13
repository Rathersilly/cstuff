#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <stdexcept>
using namespace std;


// Catching zero division error message
//https://stackoverflow.com/questions/6121623/catching-exception-divide-by-zero
int main() {
	int i = 0;	
		//throw runtime_error("hi there");
	try	{
		throw overflow_error("hello there");
		i = 1/0;
	} catch(string e) {
		cout << e << endl;
	}


	// these also work:
	
	/* catch (std::overflow_error e ) {
		cout << e.what() << endl;
	}


	/*catch (string e_msg) {
		cout << e_msg << endl;

}
*/




}

