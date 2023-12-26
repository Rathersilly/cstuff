#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
vector<int> twosum(vector<int> &nums, int target) {
  vector<int> output{1, 2};
  int i = 0;
  for (auto a : nums) {
    if (i == nums.size()) {
      break;
    } else {
      for (int j = i; j < nums.size(); ++j) {
        if (a + nums[j] == target)
          return {a, nums[j]};
      }
    }
    ++i;
  }

  return output;
}

int main(int argc, char *argv[]) {

  vector<int> input{2, 7, 11, 15};
  vector<int> result = twosum(input, 9);
  for (auto &a : result) {

    cout << a << endl;
  }
}
