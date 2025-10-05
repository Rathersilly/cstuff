// g++ -std=c++20 foo.cpp -lCatch2Main -lCatch2
// This can be a demo of Catch2 - symlinked to Catch2demo.cpp
#include "object_pool.h"
#include <color_macros.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

CATCH_REGISTER_TAG_ALIAS("[@PoolTemplate]", "[ObjectPool][Object]~[.]");
// TEST_CASE("Correct Object Pool Size", "[ObjectPool]") {

using MyTypes = std::tuple<int, char, float>;
TEMPLATE_LIST_TEST_CASE("Test w/ above types", "[template][list]", MyTypes) {}

TEMPLATE_TEST_CASE("ObjectPool Test", "[ObjectPool]", Object /*, int */) {
  // for each section, this code is executed anew
  // ie this is the setup section

  size_t pool_size = 10;
  ObjectPool<TestType> pool(pool_size, true);
  // ObjectPool<Object> pool(pool_size);
  // Object *obj = pool.create("bob", 0);
  // ObjectPool<Object> pool(10);
  // Object *obj = pool.create("bob", 0);

  // CHECK will continue running on failure
  // REQUIRE will halt program on failure
  CHECK(pool.size_ == pool_size);
  CHECK(pool.data_[3].id_ == 3);
  REQUIRE(pool.data_[5].id_ == 5);
  SECTION("Pool Initialization") {
    ObjectPool<TestType> test_pool(pool_size, false);
    REQUIRE(test_pool.first_unused_ == nullptr);

    test_pool.initialize();
    REQUIRE(pool.data_[0].next_unused_ == &(pool.data_[1]));
    REQUIRE(pool.data_[pool_size - 1].next_unused_ == nullptr);
  }

  // SECTION has aliases SCENARIO, GIVEN, WHEN, THEN,
  //                     AND_GIVEN, AND_WHEN, AND_THEN
  SECTION("Create Uninitialized Pool", "[ObjectPool]") {
    ObjectPool<TestType> u_pool(10);
    CHECK(pool)

    CHECK(pool.size_ == pool_size);
    cout << pool.check_name(0) << endl;
    cout << pool.check_name(2) << endl;
    SECTION("Nested") {
      cout << "sections can be nested to share setup" << endl;
    }
  }
  cout << pool.data_[3].id_ << endl;
  cout << pool.data_[5].id_ << endl;
  cout << pool.data_[3].next_unused_->id_ << endl;
  cout << boolalpha << (pool.data_[8].next_unused_ == nullptr) << endl;
  cout << (pool.data_[9].next_unused_ == nullptr) << endl;
}
