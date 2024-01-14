// LearnCPP ch 20 fuctions & funtion pointers
// TODO the quiz seems great - create simple calculator function
#include <algorithm>  //std::shuffle
#include <chrono>     // std::chrono::high_resolution_clock / system_clock
#include <functional> // std::function
#include <iostream>
#include <random>
#include <vector>
using namespace std;

template <typename T> void print_vector(const vector<T> &v) {
  for (auto i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  cout << endl;
}
bool ascending(int a, int b) { return a > b; }
bool descending(int a, int b) { return a < b; }

bool evensFirst(int x, int y) {
  // if x is even and y is odd, x goes first (no swap needed)
  if ((x % 2 == 0) && !(y % 2 == 0))
    return false;

  // if x is odd and y is even, y goes first (swap needed)
  if (!(x % 2 == 0) && (y % 2 == 0))
    return true;

  // otherwise sort in ascending order
  return ascending(x, y);
}

// type aliases are great for readability
using ValidateFunction = bool (*)(int, int);
using ComparisonFunction = bool (*)(int, int);
using anotherFunction = std::function<bool(int, int)>;

void selectionSort(vector<int> &vec, ComparisonFunction compFun = ascending) {
  /* void selectionSort(vector<int> &vec, bool comparisonFcn(int, int) =
   * ascending) { */

  for (int start_index = 0; start_index < vec.size(); ++start_index) {
    int best_index{start_index};
    for (int current_index = start_index + 1; current_index < vec.size();
         ++current_index) {
      /* if (comparisonFcn(vec[best_index], vec[current_index])) { */
      if (compFun(vec[best_index], vec[current_index])) {
        best_index = current_index;
      }
    }
    std::swap(vec[start_index], vec[best_index]);
  }
}

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

int main(int argc, char *argv[]) {
  // Create a reusable random number generator that generates uniform numbers
  // between 1 and 6
  std::mt19937 mt{std::chrono::system_clock::now().time_since_epoch().count()};
  std::uniform_int_distribution<> die10{0, 9};
  vector<int> v;

  // create vector 0-9 shuffled
  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }
  std::shuffle(v.begin(), v.end(), mt);

  print_vector(v);
  selectionSort(v, descending);
  print_vector(v);
  selectionSort(v, ascending);
  print_vector(v);

  // create vector with 10 random ints 0-9
  v.clear();
  for (int i = 0; i < 10; ++i) {
    v.push_back(die10(mt));
  }

  selectionSort(v, evensFirst);
  print_vector(v);

  // creating a function pointer
  int (*fptr)(int, int){&add};
  int (*fptr2)(int, int);
  std::function<int(int, int)> fptr3 = &add;

  // making it point to another function (params must agree)
  // *** default params don't work - they are resolved at compile time
  fptr = &subtract;
  fptr2 = &add;

  // these oddly dont seem to produce errors - they just output 0
  fptr2 = nullptr;
  cout << fptr2 << endl;
  cout << *fptr2 << endl;

  int a = 2;
  int b = 3;

  // calling a function pointer:
  // explicit dereference
  cout << (*fptr)(a, b) << endl;
  // implicit dereference
  cout << fptr(b, a) << endl;
}
