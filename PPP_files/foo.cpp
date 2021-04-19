#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <string>
using namespace std;

// ppp ch20 - Document class
// not finished - find_text and related fns dont work
using Line = vector<char>;

class Text_iterator {
	list<Line>::iterator ln;
	Line::iterator pos;
	public:
	Text_iterator(list<Line>::iterator ll,Line::iterator pp)
		: ln{ll},pos{pp} {}

	char& operator*() { return *pos; }
	Text_iterator& operator++();
	bool operator==(const Text_iterator&) const;
	bool operator!=(const Text_iterator&) const;
	

};

bool Text_iterator::operator==(const Text_iterator& other) const
{
	return ln == other.ln && pos == other.pos;
}

bool Text_iterator::operator!=(const Text_iterator& other) const
{
	return !(*this == other);
}
Text_iterator& Text_iterator::operator++()
{
	++pos;
	if (pos == (*ln).end()) {
		++ln;
		pos = (*ln).begin();
	}
	return *this;
}

struct Document {
	list<Line> line;



	Document() { line.push_back(Line{});}
	Text_iterator begin() 
	{
		return Text_iterator(line.begin(),(*line.begin()).begin());
	}

	Text_iterator end()
	{
		auto last = line.end();
		--last;
		return Text_iterator(last, (*last).end());
	}


};

istream& operator>>(istream& is, Document& d)
{
	for(char ch; is.get(ch);) {
		d.line.back().push_back(ch);
		if (ch=='\n') { d.line.push_back(Line{}); }
	}
	if(d.line.back().size()) { d.line.push_back(Line{}); }
	return is;
}

void erase_line(Document& d, int n)
{
	if (n < 0 || n >= d.line.size()-1) return;
	auto p = d.line.begin();
	advance(p,n);
	d.line.erase(p);
}

template<typename Iter>
void advance(Iter& p, int n)
{
	if (n >= 0) {
		while(0 < n) {
			++p;
			--n;
		}
	}
	else {
		while(n < 0) {
			--p;
			++n;
		}
	}
}

bool match(Text_iterator first, Text_iterator last, const string& s)
{INFO
	string mstring = "";
	for(auto a = first;a != last;++a) {
		mstring += *a;
	}
	if (mstring == s) {
		cout << "match found" << endl;
		return true;
	}
	cout << "match NOT found" << endl;
	return false;
}

Text_iterator find(Text_iterator first, Text_iterator last, const char& s)
{INFO
	for(auto a = first;a != last;++a) {
		cout << "s: " << setw(4) << s << "*a" <<
			setw(4) << *a << endl;

		if (s ==  *a) return a;
	}
	return last;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
{INFO
	if (s.size() ==0) return last;
	char first_char = s[0];
	while(true) {
		auto p = find(first,last,first_char);
		if(p==last || match(p,last,s)) return p;
		first = ++p;
	}
}

void print(Document& d)
{
	for(auto a : d) { cout << a; }
}

int main()
{
	Document d;
	cin >> d;

	erase_line(d,2);

	print(d);

	auto p = find_txt(d.begin(),d.end(),"op");
	cout << *p;

}
