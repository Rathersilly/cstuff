#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

// PPP ch20 drills

template<typename Iter1,typename Iter2>
Iter2 mycopy(Iter1 f1,Iter1 e1,Iter2 f2)
{
	while(f1 != e1) {
		*f2 = *f1;
		++f1;
		++f2;
	}
	return f2;
}
template<typename T>
void print(T* beg,T* end)
{
	while(beg != end) {
		cout << *beg << " ";
		++beg;
	}
	cout << endl;
}

template<typename T>
void print(const T& box)
{
	for(auto a = box.begin();a != box.end();++a) {
		cout << *a << " ";
	}
	cout << endl;
}


int main()
{
	cout << "*** drills 1-5: creating different containers" << endl;
	int a[10] = {};
	for(int i=0;i<10;++i){
		a[i] = i+1;
	}
	cout << a[4] << endl;

	vector<int> v(10);
	for(int i=0;i<10;++i){
		v[i] = i+1;
	}
	cout << v[4] << endl;

	list<int> l;
	for(int i=0;i<10;++i){
		l.push_back(i+1);
	}
	for(auto a = l.begin();a!= l.end();++a) {
		cout << *a << " ";
	}
	cout << endl;

	int a2[10];
	for(int i=0;i<10;++i){
		a2[i] = a[i];
	}
	cout << a2[4] << endl;

	vector<int> v2 = v;
	cout << v2[4] << endl;
	
	list<int>l2 = l;
	for(auto a = l.begin();a!= l.end();++a) {
		cout << *a << " ";
	}
	cout << endl;

	for(int i=0;i<10;++i){
		a[i] = a[i] + 2;
	}
	cout << a[4] << endl;

	for(auto a = v.begin();a!= v.end();++a) {
		*a = *a + 3;
	}
	cout << v[4] << endl;
	cout << endl;

	for(auto a = l.begin();a!= l.end();++a) {
		*a = *a + 4;
		cout << *a << " ";
	}
	cout << endl;


	vector<int> v3(10);

	cout << "*** drills 6-7: mycopy function" << endl;
	vector<int>::iterator x = mycopy(v.begin(),v.begin()+4,v3.begin());
	print(v3);
	cout << *(--x) << endl;

	cout << "using STL array" << endl;
	array<int,10> aaa;
	mycopy(l.begin(),l.end(),aaa.begin());
	
	cout << "checking both versions of mycopy work" << endl;
	print(aaa.begin(),aaa.end());
	print(aaa);

	cout << "*** drill 8 - STL find()" << endl;
	auto thing = find(v.begin(),v.end(),7);
	if (thing != v.end()) {
		cout << "found: " << *thing << endl;
	}
	else {
		cout << "not found" << endl;
	}
	thing = find(v.begin(),v.end(),17);
	if (thing != v.end()) {
		cout << "found: " << *thing << endl;
	}
	else {
		cout << "not found" << endl;
	}




}
