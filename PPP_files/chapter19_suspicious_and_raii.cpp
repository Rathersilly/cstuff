//
// ppp ch 19.5+ - resources, exceptions, RAII

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

// 19.5.4 unique_ptr
// unique_ptr can't be assigned to another unique_ptr
// and 2  unique_ptrs cant point to same object
// deleting the  unique_ptr will delete the object
// shared_ptr also exists, but is more overhead

// this function will not leak when throwing, but someone
// must remember to delete p later
vector<int>* make_vec() 		// make a filled vector
{
	unique_ptr<vector<int>> p {new vector<int>};	// allocate from heap
	// fill the vector with data; this may throw an exception
	return p.release();					// return the pointer held by p
}

// but if we return a unique_ptr, its all good
unique_ptr<vector<int>> make_vec() 		// make a filled vector
{
	unique_ptr<vector<int>> p {new vector<int>};	// allocate from heap
	// fill the vector with data; this may throw an exception
	return p;
}

// 19.5.5 return by moving - the best solution
// provides simplicity and safetey
vector<int> make_vec()
{
	vector<int> res;
	// fill the vector with data; this may throw an exception
	return res;
}

// 19.5.6 RAII for vector
// this has the advantage of avoiding new and delete completely
// a bit more stuff to grok but its super effing safe
template<typename T,typename A = allocator<T>>
struct vector_base {
	A Alloc;
	T* elem;
	int sz;
	int space;

	vector_base(const A& a, int n)
		: alloc{a},elem{alloc.allocate(n)},space{n} {}
	~vector_base() {alloc.deallocate(elem,space);}
};

// then have vector inherit from vector_base
template<typename T,typename A = allocator<T>>
class vector : private vector_base<T,A> {
	// ...
};

// then reserve() becomes simpler and more correct
// new stdlib functions:
//
// template< class InputIt, class ForwardIt >
// std::uninitialized_copy(InputIt first,InputIt last,ForwardIt d_first) - first-last is range to copy
// 		d_first is start of destination
// template< class T >
// std::swap(T&a,T&b) - what it says on the tin
template<typename T,typename A>
void vector<T,A>::reserve(int newalloc)
{
	if(newalloc<=capacity()) return; 				// never decrease allocation
	vector_base<T,A> b {this->alloc,newalloc}		// allocate new space
	uninitialized_copy(this->elem,this->elem+size(),b.elem);	// copy
	for(int i=0;i<sz;++i)
		{this->alloc.destroy(&this->elem[i]);}		// destroy
	swap<vector_base<T,A>>(*this,b);				// swap representations
}
int main()
{



}
