#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

// Sieve of Eratosthenes function

vector<int> sieve(vector<int> nums, vector<int> &primes) {
	if (nums.size() == 0) {
		return primes;
	}
	primes.push_back(nums[0]);
	vector<int> nums2;
	
	for(auto i = 1; i < nums.size(); i++) {
		cout << "i: " << i << " nums[i]: " << nums[i] <<  " nums[0]:" << nums[0] << endl;
		if (nums[i] % nums[0] != 0) {
			nums2.push_back(nums[i]);
		}
	}
	return sieve(nums2, primes);
}

int main() {
	vector<int> nums;
	vector<int> primes;
	for(int i = 2; i < 101; i++) {
		nums.push_back(i);
	}
	primes = sieve(nums, &primes);
	for(auto i = 0; i < primes.size(); i++) {
		cout << primes[i] << endl;
	}
}
