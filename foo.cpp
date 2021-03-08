
#include <string>
#include <iostream>
#include <fstream>
//#include <vector>
//#include <deque>
//#include <list>
#include <forward_list>
#include <cmath>
using namespace std;

// doing ch9 of C++ Primer - containers stuff
// erase is doing wonkythings - segfault
void display(forward_list<int> x){

	for(auto i = x.begin(); i != x.end();i++) {
		cout << *i << " ";
	}
	cout << endl;

}


int main() {
	forward_list<int> a {1,2,3,4};
	a.insert_after(a.begin(),5);
	
	display(a);
	cout << *a.begin() << endl;





}
