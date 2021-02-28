#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Token {
	public:

	char kind;
	double value;


};
Token get_token();
double expression();
double term();
double primary();
vector<Token> tok;

int main() {
	cout << "please enter expression: " << endl;
	string exp = "3+4*3";
	




  return 0;
}
double expression() {
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

}

