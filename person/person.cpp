#include <iostream>
#include <string>
#include "person.h"

using namespace std;

Person::Person(string n, int a) 
	:name{n}, age{a}
	{
	//name = n;
	//age = a;
}


int main() {
	Person bob("bob", 30);
	bob.print();


	return 0;
}
