#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
	string x = "2+3+4";
	stringstream xstream(x);
	string s;
	
	int i = 0;
	while(xstream >> s) {
		cout << i << " ";
		cout << s << endl;
		++i;
	}
		


  return 0;
}
