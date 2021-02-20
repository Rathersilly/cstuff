#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

// in Ch 9 of C++ Primer
#include <iostream>
#include <bitset>

int main() {
    int a = -58, b = a>>3, c = -315;

	int d = 96;
	int e = -96;
	int i = 300;
	char x = i;

    std::cout << "a = " << std::bitset<8>(a)  << std::endl;
    std::cout << "b = " << std::bitset<8>(b)  << std::endl;
    std::cout << "a = " << std::bitset<16>(a)  << std::endl;
    std::cout << "b = " << std::bitset<16>(b)  << std::endl;
    std::cout << "c = " << std::bitset<16>(c) << std::endl;
    std::cout << "d = " << std::bitset<16>(d) << std::endl;
    std::cout << "e = " << std::bitset<16>(e) << std::endl;
    std::cout << "i = " << std::bitset<16>(i) << std::endl;
    std::cout << "x = " << std::bitset<16>(x) << " int to char is truncated" << std::endl;
}

