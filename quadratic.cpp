#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

// Quadratic equation - doesnt work for cmplex roots though yet

vector<double> quad(double a, double b, double c) {
	if ((b*b - 4 * a * c) < 0) {
		throw(range_error("will be complex roots"));
	}
	
	// x = -b +- root(b*2 - 4ac)
	// over 2a
	vector<double> x;
	double x1, x2, real, img;
	double discriminant = b*b - 4*a*c;
	if (discriminant > 0) {
		x1 = (-b + sqrt(discriminant)) / (2*a);
        x2 = (-b - sqrt(discriminant)) / (2*a);
        cout << "Roots are real and different." << endl;
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
	else if (discriminant == 0) {
        cout << "Roots are real and same." << endl;
        x1 = -b/(2*a);
        cout << "x1 = x2 =" << x1 << endl;
    }

    else {
        real = -b/(2*a);
        img = sqrt(-discriminant)/(2*a);
        cout << "Roots are complex and different."  << endl;
        cout << "x1 = " << real << "+" << img << "i" << endl;
        cout << "x2 = " << real << "-" << img << "i" << endl;
    }
	x.push_back(x1);
	x.push_back(x2);

			

	return x;
}


int main() {
	int a, b, c;
	vector<double> results;
	a = 2;
	b = -5;
	c = 2;

	//while(cin >> a, cin >> b, cin >> c) {
	try {
		results = quad(a, b,  c);
	
		for(auto p = results.begin();p != results.end();p++) {
			cout << *p << endl;
		}
	}
	catch (range_error &e) {
		cout << "exception: " << e.what() << endl;
	}


}
