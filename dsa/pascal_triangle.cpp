// Array algorithm problems from Srivistava C++ DSA ch 2
#include <algorithm>
#include <cassert>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace fmt;
using namespace std;

// Pascal Triangle and Magic Matrix functions from Srivastava's DSA with C++
void pascal_triangle(int size) {
  std::vector<std::vector<int>> arr(size);
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    std::fill_n(std::back_inserter(*it), size, 0);
  }

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (j > i) {
        arr[i][j] = 0;
      } else if (j == 0 || j == i) {

        arr[i][j] = 1;
      } else {
        arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
      }
    }
  }
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (arr[i][j] == 0)
        continue;

      print("{} ", arr[i][j]);
    }
    print("\n");
  }
}

// create a magix matrix (has the following properties):
// - nxn matrix. n must be odd.
// - elements are the numbers 1..n^2
// - elements in each row, col, diag has equal sum of n(n^2 + 1) / 2
// - elements are placed according to certain rules
void magic_matrix(int size) {
  if (size % 2 == 0)
    throw(std::invalid_argument("size must be odd"));

  std::vector<std::vector<int>> arr(size);
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    std::fill_n(std::back_inserter(*it), size, 0);
  }

  int num = 1;
  int imax = size - 1;
  int i = imax;
  int j = imax / 2;
  arr[i][j] = 1; // 1 goes in bottom middle
  ++num;
  auto index_in_bounds = [size](int i) { return i < size && i >= 0; };
  while (num < 1 + size * size) {
    ++i; // move down left
    --j;
    bool valid_square = false;

    while (!valid_square) {
      while (!index_in_bounds(i) || !index_in_bounds(j)) {
        if (i == size && j == -1) { // if we were at bottom left
          i -= 2;                   // go above prev location
          j += 1;
        } else {
          if (j == -1) { // if too far left, go to right col
            j = imax;
          } else if (i > imax) { // if too far down, to to top row
            i = 0;
          }
        }
      }
      if (arr[i][j] == 0) { // found an open spot hooray!
        valid_square = true;
      } else { // if spot is taken, move up a row
        i -= 2;
        j += 1;
      }
    }
    arr[i][j] = num++;
    // for (int i = 0; i < size; ++i) {
    //   for (int j = 0; j < size; ++j) {
    //     print("{:3} ", arr[i][j]);
    //   }
    //   print("\n");
    // }
  }
  // test magic matrixness
  std::vector<int> row_sums(size);  // sum of elements in each row
  std::vector<int> col_sums(size);  // sum of elements in each col
  std::vector<int> diag_sums{0, 0}; // sum of elements in each diag

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      row_sums[i] += arr[i][j];
      col_sums[i] += arr[j][i];
      if (i == j)
        diag_sums[0] += arr[i][j];
      if (i + j == size - 1)
        diag_sums[1] += arr[i][j];
    }
  }

  // sums should all be n(n^2 + 1) / 2
  auto target_sum_pred = [size](int a) {
    return a == size * (size * size + 1) / 2;
  };
  assert(std::ranges::all_of(row_sums, target_sum_pred));
  assert(std::ranges::all_of(col_sums, target_sum_pred));
  assert(std::ranges::all_of(diag_sums, target_sum_pred));

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      print("{:3} ", arr[i][j]);
    }
    print("\n");
  }
  print("row_sums: {}\n", row_sums);
  print("col_sums: {}\n", row_sums);
  print("diag_sums: {}\n", diag_sums);
}

// Sieve of Eratosthenes (print all primes < n)
vector<int> sieve(int n) {
  vector<bool> is_prime(n, true);
  is_prime[0] = is_prime[1] = false;

  for (int i = 2; i < n; ++i) {
    if (is_prime[i])
      for (int j = i + 1; j < n; ++j) {
        if (j % i == 0)
          is_prime[j] = false;
      }
  }

  vector<int> primes;
  for (int i = 0; i < is_prime.size(); ++i) {
    if (is_prime[i])
      primes.push_back(i);
  }
  return primes;
}

// Print Spiral Matrix - starting top left going right
void print_spiral_matrix(const vector<vector<int>> &arr) {
  int rows = arr.size();
  int cols = arr[0].size();
  int irow_min = 0; // min row to print
  int icol_min = 0;
  int irow_max = rows - 1; // max row to print
  int icol_max = cols - 1;

  while (irow_min <= irow_max && icol_min <= icol_max) {

    for (int i = icol_min; i <= icol_max; ++i) { // right
      cout << arr[irow_min][i] << " ";
    }
    irow_min++;
    for (int i = irow_min; i <= irow_max; ++i) { // down
      cout << arr[i][icol_max] << " ";
    }
    icol_max--;
    for (int i = icol_max; i >= icol_min; --i) { // left
      cout << arr[irow_max][i] << " ";
    }
    irow_max--;
    for (int i = irow_max; i >= irow_min; --i) { // up
      cout << arr[i][icol_min] << " ";
    }
    icol_min++;
  }
  cout << endl;
}
void test_spiral_matrix() {
  cout << "Printing spiral matrix:\n";
  int rows = 7, cols = 7;
  vector<vector<int>> arr(rows, vector<int>(cols));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      arr[i][j] = i * cols + j;
    }
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      // print("{:3} ", arr[i][j]);
      cout << setw(3) << arr[i][j] << " ";
    }
    cout << endl;
  }
  print_spiral_matrix(arr);
}

int main() {
  const int size = 13;
  pascal_triangle(size);
  magic_matrix(size);

  int n = 100;
  vector<int> primes = sieve(n);
  print("primes < {}: {}\n", n, primes);
  test_spiral_matrix();
}
