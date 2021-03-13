//
// uh, this file is all messed up plz ignore!
//
struct Reading {
	int day;
	int hour;
	double temp;
	Reading(int h, double t) :hour(h), temp(t) {}
};

void print(vector<string> s, ostream& os = cout) {
	for(auto a = s.begin();a != s.end();a++) {
		os<< *a << endl;
	}
}
void print(vector<Reading> s, ostream& os = cout) {
	for(auto a = s.begin();a != s.end();a++) {
		os<< "Hour " << a->hour << ": " << a->temp << " degrees." << endl;
	}
}
/*vector<string> read(istream& is = cin) {
	vector<string> v;
	string s;
	while(is >> s) {
		v.push_back(s);
	}
	return v;
}
*/
/*vector<Reading> read( istream& is = cin) {
	vector<Reading> r;
	int h; double t;
	while(is >> h >> t) {
		r.push_back(Reading(h,t));
	}
	return r;
}*/
	string ifilename = "input.txt";
	ifstream ist(ifilename.c_str());
	ist.clear(ios_base::failbit);
	try {
		if (!ist) throw(invalid_argument("cant do that"));
	}
	catch (invalid_argument& e) {
		cout << e.what() << endl;
		cout << "carrying on" << endl;
	}
	
	//while(ist>>s) v.push_back(s);
	//v = read(ist);
	cout << "here now" << endl;
	print(v);
	//print(temps);



	

