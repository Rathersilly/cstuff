
#include <string>
#include <sstream>
#include <iostream>
//#include <fstream>
#include <vector>
//#include <list>
//#include <cmath>
//#include "goo.h"
//#include <unistd.h>
//#include <climits>          /// INT_MAX
#include <algorithm>

using namespace std;

// ppp exercise 9.2
// needed cin.clear() to clear EOF char from stream (ie Ctrl-D)

void swap(int& a, int& b) { int t = a; a = b; b = t;}
void print(vector<int> v, string s = "hi there") {
	cout << s << endl;
	for(int i =0; i<v.size();i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}
class Name_pairs {
	public:
		void print() {
			cout << "printing" << endl;
			for(int i = 0;i< names.size();i++) {

				cout << names[i] << " is " << ages[i] << " years old." << endl;
			}

		}

		void read_names() {
			while(cin >> n) {
				names.push_back(n);
			}
			clearerr(stdin);
		}
		void read_ages() {
			//fflush(stdin);
			//clearerr(stdin);
			//fflush(stdin);
			//cin.ignore(INT_MAX, '\n');

			cout << "Please enter age for each name: " << endl;
			string::size_type sz;
				char sage[100];
			for(int i = 0;i < names.size();i++) {
				cout << names[i] << ": ";// << flush;
				//fflush(stdout);
				//fflush(stdin);
				//clearerr(stdin);
				//fflush(stdin);
				//cin.ignore(INT_MAX, '\n');
				cin.clear();
				//cin.ignore(std::numeric_limits<std::streamsize>::max());
				//fflush(stdin);
				//cin.ignore();

				    //cin.ignore(INT_MAX, '\n');

				cin >> sage;
				//cin.getline(sage,'\n');
				//cout << endl;
				//ages[i] = stoi(sage,&sz);
				//ages[i] = stod(sage,nullptr);//,&sz);
				
				//sages.push_back(sage);
				ages.push_back(stod(sage));
			}
		}
		void sort() {
			vector<string> oldnames(names);
			vector<double> oldages(ages);
			std::sort(names.begin(), names.end());
			for(int i = 0; i < ages.size();i++) {
				for(int j = 0; j < ages.size();j++) {
					if (oldnames[j] == names[i]) {
						ages[i] = oldages[j];
					}
				}
			}
			print();


		}
	private:
		string n;
		vector<string> names;
		vector<double> ages;
		vector<string> sages;




};

int main() {
	Name_pairs n;
	n.read_names();
	n.read_ages();
	n.print();
	n.sort();
}
