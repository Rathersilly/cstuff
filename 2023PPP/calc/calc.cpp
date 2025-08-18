#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
class Token {
	public:

	char kind;
	double value;
	Token(char ch)
		:kind(ch), value(0) {}
	Token(char ch, double val)
		:kind(ch), value(val) {}

};
Token get_token();
double expression();
double term();
double primary();
vector<Token> tok;

int main() {
	string ex = "2 + 3+4";
	stringstream exstr(ex);
	string t;

	try {
		cout << "please enter expression: " << endl;
		while (exstr >> t) {
			if (t== "+") {
				tok.push_back(Token('+'));
			}
			else if (t== "2") {
				tok.push_back(Token('n', stoi(t)));
			}

		cout << t << endl;
		}
	}
	//string exp = "3+4*3";
	catch (exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	/*catch (...) {
		cerr << "exception \n";
		return 2;
	}*/




  return 0;
}
double expression() {
	cout << "in exp" << endl;
	double left = term();
	Token t = get_token();
	while (t.kind=='+' || t.kind=='-') {

		switch(t.kind) {
		case '+':
			left += term();
			t = get_token();
			break;
		case '-':
			left -= term();
			t = get_token();
			break;
		default:
			return left;
		}
	}
}
double term() {
	cout << "in term" << endl;
	double left = primary();
	Token t = get_token();
	while(true) {
		switch(t.kind) {
		case '*':
			left *= primary();
			t = get_token();
			break;
		case '/':
		// need block here in order to define and init variable within switch
		{
			double d = primary();
			if (d==0) throw("divide by zero");
			left /= d;
			t = get_token();
			break;
		}
		default:
			return left;
		}
	}
}
double primary() {
	cout << "in prim" << endl;
	Token t = get_token();
	switch(t.kind) {
		case '(':
			{	double d = expression();
				t = get_token();
				if(t.kind != ')') throw("')' expected");
				return d;
			}
		case '8':
			return t.value;
		default:
			throw("primary expected");
	}
}

Token get_token() {



}
					  
			


