#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>		// std::function
using namespace std;

// PPP ch21 21.5 Numerical algorithms

template<typename In,typename T,typename BinOp>
T my_accumulate(In first,In last,T init,BinOp op)
{
	while(first != last) {
		init = op(init, *first);
		++first;
	}
	return init;
}

template<typename In,typename In2,typename T, typename BinOp, typename BinOp2>
T my_inner_product(In first,In last,In2 first2,T init,BinOp op,BinOp2 op2)
{
	while(first != last) {
		init = op(init,op2(*first, *first2));
		++first;
		++first2;
	}
	return init;
}

int main()
{
	vector<int> v1 {1,2,3};
	vector<int> v2 {1,3,5};

	// starting with init = 10, add to init all the elements of v1
	int x =  my_accumulate(v1.begin(),v1.end(),10,[](int a,int b){return a+b;});
	cout << x << endl;
	

	// starting with init = 0, multiply pairs of values from v1 and v2 and add them to init
	x = my_inner_product(v1.begin(),v1.end(),v2.begin(),0,
			[](int a,int b){return a+b;},
			[](int a,int b){return a*b;});
	cout << x << endl;
}





