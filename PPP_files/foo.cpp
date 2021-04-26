#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>		// std::function
#include <map>		// std::function
using namespace std;

// PPP ch21 vector drills

struct Item {
	string name;
	int iid;
	double value;
	Item(string n,int id,double v) : name(n),iid(id),value(v) {}
};
bool operator<(Item a,Item b)
{
	if (a.name < b.name) return true;
	return false;
}
bool operator==(Item a,Item b)
{
	if (a.name == b.name) return true;
	return false;
}
bool operator==(Item a,string b)
{
	if (a.name == b) return true;
	return false;
}

bool itemcmp(Item a, Item b)
{
	return a.iid < b.iid;
}
bool itemnamecmp(string s,Item a)
{
	return s == a.name;
}

void print(vector<Item> vi)
{
	for(auto a = vi.begin();a != vi.end();++a) {
		cout << a->name << " " << a->iid << " " << a->value << endl;
	}
	cout << endl;
}
void erase_by_name(vector<Item>& v,string s)
{INFO
	auto x = find(v.begin(),v.end(),s);
	cout << "Erasing: " << x->name << endl;
	auto i = v.begin();
	vector<Item> memo;
	while(i != v.end()){
		if (i!=x) memo.push_back(*i);
		++i;
	}
	v = memo;



}

// this doesnt quite work right - erases but needs to delete last item still
void erase_by_name_try2(vector<Item>& v,string s)
{

	auto x = find(v.begin(),v.end(),s);
	if (x + 1 == v.end() || x == v.end()) return;
	auto i = v.begin();
	while(x != v.end() - 1){
		*x = *(x+1);
		++x;
	}
	v.end() = x;



}

	

int main()
{
	vector<Item> vi;
	vi.push_back(Item{"hammer",2,79.2});
	vi.push_back(Item{"broom",1,45.5});
	vi.push_back(Item{"hammer",2,79.2});
	vi.push_back(Item{"broom",1,45.5});
	print(vi);
	sort(vi.begin(),vi.end(),itemcmp);
	print(vi);

	
	Item a{"broom",1,45.5};

	// searching for a in vi - had to define opeartor< (and i think operator==)
	auto x = binary_search(vi.begin(),vi.end(),a);
	cout << x << endl;
	print(vi);

	// have to define insert for vector<Item>
	vi.insert(vi.begin(),a);
	print(vi);

	vi.erase(vi.end());
	print(vi);

	// idk i might have done this a horribly wrong way - basically copied the vector in the function
	erase_by_name(vi,"broom");
	print(vi);

	erase_by_name_try2(vi,"broom");
	print(vi);

	erase_by_name_try2(vi,"broom");
	print(vi);
}
	

