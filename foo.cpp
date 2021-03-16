#include <string>
//#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
//#include <list>
//#include <cmath>
//#include "goo.h"
//#include <unistd.h>
//#include <climits>          /// INT_MAX
//#include <algorithm>
using namespace std;

// PPP ch 10 (iostreams) exercises
struct Point {
		int x;
		int y;
		Point();
		Point(int, int);
};
Point::Point() {}
Point::Point(int a, int b) : x(a), y(b) {}



int main() {


	Point a;
	a.x = 1;
	a.y = 2;
	cout << a.x << " " << a.y << endl;

	ofstream ofs("zxcv", ios::app);
	ofs << a.x << " " << a.y << endl;
	ofs.close();
	ifstream ifs("zxcv");
	vector<Point> pts;
	Point p;
	int x,y;
	while(ifs >> x >> y) {

		pts.push_back(Point(x,y));
	}
	cout << "printing:" << endl;
	for(auto a = pts.begin();a != pts.end();a++) {
		cout << a->x << " ";
		cout << a->y << " ";
		cout << endl;
	}
	ifs.clear();
	ifs.seekg(0, ios::beg);
	int sum = 0;
	int z = 0;
	while ( ifs >> z ) {
		sum += x;
	}
	cout << sum;

}

