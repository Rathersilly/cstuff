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
  Matrix2d a;
  a << 1, 2,
       3, 4;
  MatrixXd b(2,2);
  b << 2, 3,
       1, 4;
  std::cout << "a + b =\n" << a + b << std::endl;
  std::cout << "a - b =\n" << a - b << std::endl;
  std::cout << "Doing a += b;" << std::endl;
  a += b;
  std::cout << "Now a =\n" << a << std::endl;
  Vector3d v(1,2,3);
  Vector3d w(1,0,0);
  std::cout << "-v + w - v =\n" << -v + w - v << std::endl;
  a+= b;

  cout << a;
}
