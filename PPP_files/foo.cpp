#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>		// std::function
#include <map>		// std::function
using namespace std;

// PPP ch21 

template<typename Key,typename Value,typename Cmp = less<Key>>
	// requires Binary_operation<Cmp,Value>
class map {
	using value_type = pair<Key,Value>;		// a map deals in (key,value) pairs

	using iterator = sometype1;
	using const_iterator = sometype2;

int main()
{

	map<string,int> words;
	for(string s;cin >> s;) {
		++words[s];
	}

	for(const auto& p : words) {
		cout << p.first << ": " << p.second << endl;
	}
	cout << words["hello"] << endl;
	++words["hi"];
	cout << words["hi"] << endl;
	for(const auto& p : words) {
		cout << p.first << ": " << p.second << endl;
	}

}

