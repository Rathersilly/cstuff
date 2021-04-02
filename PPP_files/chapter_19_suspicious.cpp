
// ppp ch 19.5 - resources and exceptions


void suspicious(int s,int x)
	// what are the things that could go wrong
	// between the new and the delete?
{
	int* p = new int[s];		// acquire memory
	//...
	if(x) p = q;				// make p point to another object
	if(x) return;				// we never get to the delete
	vector<int> v;
	if(x) p[x] = v.at(x);		// we throw exception

	// can try fixing it this way (bad or at best, naive)
	try {
		if(x) p[x] = v.at(x);
		// ...
	}
	catch (...) {				// catch every exception
		delete[] p;				// release memory
		throw;					// rethrow the exception
	}



	delete[] p;					// release memory
}

// consider acuiring more resources
// would need such try blocks as above - ugly ugly repetitive code
void suspicious2(vector<int> v,int s)
{
	int* p = new int[s];		// acquire memory
	vector<int> v1;
	// ...
	int* q = new int[s];
	vector<double> v2;
	// ...
	delete[] p;
	delete[] q;
}

// the solution - RAII - Resource acquisition is initialization
// the resource (memory in this case) is acquired by a constructor
// and release by the matching destructor
// notice that p and q aren't pointers, so we can't return without
// calling their destructors
void f(vector<int>& v,int s)
{
	vector<int> p(s);
	vector<int> q(s);
	// ...
}

// 19.5.3 Guarantees
// the basic guarantee: the function either succeeds or throws without having
// 		leaked any resources
// 	the strong guarantee: if (in addition to basic guarantee) a function also ensures
// 		that all observable(ie non local to the function) values are the same after
// 		the failure as they were when we called the function - the ideal outcome
// 	the no-throw guarantee: avoid throw, new, and dynamic cast of reference types
//
vector<int>* make_vec()					// make a filled vector
{
	vector<int>* p = new vector<int>;	// we allocate from heap
	try {
		// fill the vector with data; this may throw an exception
		return p;
	}
	catch (...) {
		delete p;		// do our local cleanup
		throw;			// rethrow to allow our caller to deal with the fact
						// that make_vec() couldnt do what it was required of it
	}
}

int main()
{



}
