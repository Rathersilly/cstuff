#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
// #include <string>
// #include <string.h>
// #include <sstream>
// #include <fstream>
// #include <vector>
// #include <fstream>
#include <iostream>
#include <iomanip>			// setprecision(n), setw
//#include <list>
//#include <cmath>
//#include "goo.h"
//#include <unistd.h>
//#include <climits>          /// INT_MAX
//#include <algorithm>
//#include <unistd.h> 		// usleep
#include <math.h>
// #include <stdlib.h> 		// srand, rand
// #include <typeinfo>			// typeid 

using namespace std;

// honestly, compile time feels the same with any of these
//#include <Eigen/Dense>
#include <Eigen/Core>
//#include <Eigen/Sparse>

// MatrixXd type is X dimensional matrix of type double
using Eigen::MatrixXd;
// how to make alias
using matrix = Eigen::MatrixXd;

using namespace Eigen;


int main()
{
	//MatrixXd m(2,2);
	// matrix m(2,2);
	// m(0,0) = 3;
	// m(1,0) = 2.5;
	// m(0,1) = -1;
	// m(1,1) = m(1,0) + m(0,1);
	// std::cout << m << std::endl;


	MatrixXd m = MatrixXd::Random(3,3);
	m = (m + MatrixXd::Constant(3,3,1.2)) * 50;
	cout << "m =" << endl << m << endl;
	VectorXd v(3);
	v << 1, 2, 3;
	cout << "m * v =" << endl << m * v << endl;

	MatrixXd n = MatrixXd::Random(3,3);
	cout << "n =" << endl << n << endl;

	cout << m(1,1);

}


