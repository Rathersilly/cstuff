// g++ -std=c++20 foo.cpp -lCatch2Main -lCatch2
// NOTE: this could become reference for Catch2
#include "my_unordered_set.h"
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/internal/catch_section.hpp>
#include <color_macros.h>
#include <limits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
using namespace Catch::Generators;

TEST_CASE_METHOD(myUnorderedSet<int>, "Create Employee/No Name", "[create]") {
  REQUIRE(bucket_count_ == 5);
}

// TODO: find out how to test <TestType> with set - guess cant test specific
// things
TEMPLATE_TEST_CASE("myUnorderedSet Test", "[myUnorderedSet][template]", int/*,
                   string , int, (std::tuple<int,float>)*/) {

  SECTION("Integers") {
    size_t initial_buckets = 10;
    myUnorderedSet<int> set(initial_buckets);
    REQUIRE(set.size() == 0);
    cerr << "here" << endl;

    auto initial_min = -2;
    auto initial_max = 10;
    auto initial_size = initial_max - initial_min;
    for (int i = initial_min; i < initial_max; ++i)
      set.insert(i);

    REQUIRE(set.size() == initial_size);
    REQUIRE(set.bucket_count() == initial_buckets);

    SECTION("insert/remove") {
      // auto num = GENERATE(-1000, -1, 0, 1, 3, 5, 1000);
      auto included = RandomIntegerGenerator<int>(
          initial_min, initial_max, 2); // std::random_device{}());
      auto excluded = FixedValuesGenerator<int>{
          numeric_limits<int>::min(), -100000, -1000, -10, 10, 1000, 1000000,
          numeric_limits<int>::max()};

      REQUIRE(set.contains(included.get()) == true);
      REQUIRE(set.contains(excluded.get()) == false);
      REQUIRE(set.count(included.get()) == 1);
      REQUIRE(set.count(excluded.get()) == 0);

      REQUIRE(set.contains(included.get() + 30) == false);
      REQUIRE(set.contains(included.get() - 30) == false);

      set.insert(included.get()); // try add 2nd included.get() to set
      REQUIRE(set.contains(included.get()) == true);
      REQUIRE(set.count(included.get()) == 1);
      REQUIRE(set.size() == initial_size);

      set.remove(included.get());
      REQUIRE(set.count(included.get()) == 0);
      REQUIRE(set.size() == initial_size - 1);
      REQUIRE(set.contains(included.get()) == false);
      REQUIRE(set.contains(included.get() + 30) == false);

      // test remove all after impl iterators
    }
    SECTION("Load factor") {
      myUnorderedSet<int> load_test_set(10);
      REQUIRE(set.load_factor() == 0);
    }
  }

  // SECTION("Strings") {}
  // myUnorderedSet<string> sset;
  // sset.insert("hello");
  // sset.insert("hi");
  // sset.insert("whatsup");
  // sset.insert("whatssup");
  // sset.insert("whattsup");
  // sset.insert("whatqsup");
  // sset.insert("whatfsadsup");
  //
  // SECTION has aliases SCENARIO, GIVEN, WHEN, THEN,
  //                     AND_GIVEN, AND_WHEN, AND_THEN
  SECTION("Create") {
    SECTION("Nested") {
      // cout << "sections can be nested to share setup" << endl;
    }
  }
}
