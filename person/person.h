#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream>
using namespace std;

class Person {
	public:
		Person(std::string n, int a);
		void print();
	private: 
		string name;
		int age;
};

void Person::print() {
	std::cout << name << " is " << age << " years old." << endl;
}
#endif
