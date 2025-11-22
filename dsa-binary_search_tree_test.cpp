#include "dsa-binary_search_tree.h"
#include <algorithm>
#include <cerrno>
#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ostream.h> // to print to std::cerr
#include <fmt/ranges.h>
#include <ios>
#include <numeric>
#include <random>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
using fmt::print;

using std::cout, std::endl;

std::mt19937 mt{std::random_device{}()};

using std::vector, std::string;

TEST_CASE("Constructor", "") {
  BinarySearchTree<int> tree;
  std::vector<int> vec(10);
  std::iota(vec.begin(), vec.end(), 0);
  std::shuffle(vec.begin(), vec.end(), mt);

  SECTION("inorder traversal") {
    for (auto n : vec) {
      cout << n << std::flush;
      tree.insert(n);
    }
    cout << endl;

    vector<int> inorder_vec = tree.inorder();
    vector<int> inorder_test(10);
    std::iota(inorder_test.begin(), inorder_test.end(), 0);

    CHECK(inorder_vec == inorder_test);
  }

  SECTION("copy constructor & assignment") {
    BinarySearchTree<int> tree1;
    BinarySearchTree<int> tree2;
    for (int i = 0; i < 10; ++i) {
      tree1.insert(i);
      tree2.insert(i + 100);
    }
    CHECK(tree1.find(0) == 1);
    CHECK(tree1.find(9) == 1);
    CHECK(tree1.find(100) == 0);
    CHECK(tree2.find(0) == 0);
    CHECK(tree2.find(100) == 1);
    CHECK(tree2.find(109) == 1);

    BinarySearchTree<int> tree3{tree1};
    CHECK(tree3.find(0) == 1);
    CHECK(tree3.find(9) == 1);
    CHECK(tree3.find(100) == 0);
    tree3 = tree2;
    CHECK(tree3.find(0) == 0);
    CHECK(tree3.find(100) == 1);
    CHECK(tree3.find(109) == 1);
  }

  SECTION("insert, find") {
    for (auto n : vec) {
      cout << n << std::flush;
      tree.insert(n);
    }
    cout << endl;

    std::vector<int> inorder_vector = tree.inorder();
    cout << std::boolalpha << tree.find(3) << " " << tree.find(-1)
         << tree.find(17) << endl;

    CHECK(tree.find(0) == true);
    CHECK(tree.find(3) == true);
    CHECK(tree.find(9) == true);
    CHECK(tree.find(10) == false);
    CHECK(tree.find(-1) == false);
    CHECK(tree.find(17) == false);
  }

  SECTION("min, max") {
    for (int i = 0; i < 3; ++i) {
      tree.insert(i);
      tree.print_header();
    }

    CHECK(tree.max() == 2);
    CHECK(tree.min() == 0);
    CHECK(tree.max() == tree.max2());
    CHECK(tree.min() == tree.min2());
  }
}
