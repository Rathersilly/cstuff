#include <iostream>
#include <string>
#include "string.h"
#include <typeinfo>
using namespace std;

int main ()
{
	int ia[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
	for (auto row = ia;row != ia + 3; row++) {
		for (auto col = *row; col != *row + 4; col++ ) {
			cout << *col << " ";
		}
	}

	cout << endl;
	cout << endl << "auto row = ia" << endl;
	for (auto row = ia;row != ia + 3; row++) {
		for (auto col = *row; col != *row + 4; col++ ) {
			cout << *col << " ";
		}
	}
	cout << endl <<"the above without the auto" << endl;
	for (int (*row)[4] = ia;row != ia + 3; row++) {
		for (int *col = *row; col != *row + 4; col++ ) {
			cout << *col << " ";
		}
	}
	cout << endl <<"const int &row[4]" << endl;
	for (const int (&row)[4] : ia ) {
		for (const int col : row ) {
			cout << col << " ";
		}
	}


	cout << endl;

	cout << endl <<"auto p = begin(ia)" << endl;
	for (auto p = begin(ia); p != end(ia); p++) {
		for (auto q = begin(*p); q != end(*p); q++) {
			cout << *q;
		}
	}


	cout << endl;
	for (auto p = begin(ia); p != end(ia); p++) {
		for (auto q = begin(*p); q != end(*p); q++) {
			*q *= *q;
		}
	}
	cout << endl;
	for (auto p = begin(ia); p != end(ia); p++) {
		for (auto q = begin(*p); q != end(*p); q++) {
			cout << *q << " ";
		}
	}
	cout << endl;
	//and of course indices:
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			ia[i][j] *= 10;
		}

	}
	cout << endl;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			cout << ia[i][j] << " ";
		}

	}
	cout << endl;





}
