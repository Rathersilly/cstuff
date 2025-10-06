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

  size_t max_pool_slots = 3;
  ObjectPool<TestType> pool(max_pool_slots, true);
  // ObjectPool<TestType> pool(max_capacity, true);
  // ObjectPool<Object> pool(capacity);
  // Object *obj = pool.acquire("bob", 0);
  // ObjectPool<Object> pool(10);
  // Object *obj = pool.acquire("bob", 0);

  // CHECK will continue running on failure
  // REQUIRE will halt program on failure
  // CHECK(pool.size_ == 10);
  // CHECK(pool.data_[3].id_ == 3);
  // REQUIRE(pool.data_[5].id_ == 5);
  // SECTION("Pool Initialization") {
  // ObjectPool<TestType> test_pool(max_capacity, false);
  // REQUIRE(test_pool.first_unused == nullptr);
  //
  // test_pool.initialize();
  // REQUIRE(pool.data_[0].next_free == &(pool.data_[1]));
  // REQUIRE(pool.data_[max_capacity - 1].next_free == nullptr);
  // }

  // SECTION has aliases SCENARIO, GIVEN, WHEN, THEN,
  //                     AND_GIVEN, AND_WHEN, AND_THEN
  SECTION("acquire Initialized Pool") {
    size_t pool_slots = 10;
    ObjectPool<TestType> pool(pool_slots, true);
    auto data = pool.data();

    CHECK(pool.num_used() == 0);
    CHECK(pool.capacity() == pool_slots);
    CHECK(data[0].in_use == false);
    CHECK(data[0].next_free == &(data[1]));

    CHECK(data[pool_slots - 1].in_use == false);
    CHECK(data[pool_slots - 1].next_free == nullptr);

    // initialize an initialized pool
    pool.initialize();
    CHECK(pool.num_used() == 0);
    CHECK(pool.capacity() == pool_slots);
    CHECK(data[0].in_use == false);
    CHECK(data[0].next_free == &(data[1]));

    CHECK(data[pool_slots - 1].in_use == false);
    CHECK(data[pool_slots - 1].next_free == nullptr);
  }

  SECTION("acquire Uninitialized Pool") {
    size_t u_pool_slots = 10;
    ObjectPool<TestType> u_pool(u_pool_slots);
    CHECK(u_pool.num_used() == 0);
    CHECK(u_pool.capacity() == u_pool_slots);

    u_pool.initialize();
    CHECK(u_pool.num_used() == 0);
    CHECK(u_pool.capacity() == u_pool_slots);
    CHECK(u_pool.capacity() == u_pool_slots);
    auto data = u_pool.data();
    CHECK(data[0].name == "none");
    CHECK(data[0].id == 0);
    CHECK(data[0].next_free == &(data[1]));
    CHECK(data[0].name == "none");
    CHECK(data[0].id == 0);
    CHECK(data[u_pool_slots - 1].next_free == nullptr);
  }
}
TEMPLATE_TEST_CASE("ObjectPool acquire", "[ObjectPool]", Object /*, int */) {
  size_t pool_slots = 3;
  ObjectPool<TestType> pool(pool_slots, true);
  auto data = pool.data();

  CHECK(data[0].name == "none");
  CHECK(data[0].id == 0);
  CHECK(data[0].in_use == false);

  TestType *obj = pool.acquire(); // acquire first
  CHECK(pool.is_empty() == false);
  CHECK(pool.num_used() == 1);
  CHECK(data[0].in_use == true);
  CHECK(obj->in_use == true);
  CHECK(obj->next_free != nullptr); // but this is false

  obj = pool.acquire("bob", 3); // acquire second
  CHECK(data[1].name == "bob");
  CHECK(data[1].id == 3);
  CHECK(data[1].in_use == true);
  CHECK(obj->in_use == true);
  cerr << "asdf" << pool.num_used() << endl;

  obj = pool.acquire("charlie", 7); // acquire third
  CHECK(obj->next_free == nullptr);

  CHECK(pool.is_full() == true);
  CHECK(pool.num_used() == pool_slots);

  // test acquiring when pool is full
  obj = pool.acquire("steve", 6);
  CHECK(obj == nullptr);

  SECTION("ObjectPool release") {
    obj = &data[1];

    cerr << "before_release" << pool.num_used() << endl;
    pool.release(obj);
    cerr << "after_release" << pool.num_used() << endl;
    CHECK(pool.is_full() == false);

    obj = pool.acquire("blerbera", 321);
    CHECK(pool.is_full() == true);

    pool.release_all();
    CHECK(pool.is_empty() == true);
    cerr << "after_release_all" << pool.num_used() << endl;
  }

  // CHECK();

  // initialize an initialized pool
  // pool.initialize();
  // CHECK(pool.num_used() == 0);
  // CHECK(pool.capacity() == pool_slots);
  // CHECK(data[0].in_use == false);
  // CHECK(data[0].next_free == &(data[1]));
  //
  // CHECK(data[pool_slots - 1].in_use == false);
  // CHECK(data[pool_slots - 1].next_free == nullptr);
}
