// NOTE: Linking Catch2:
// g++ -std=c++20 foo.cpp -lCatch2Main -lCatch2

// TODO: make this an incomplete test of my_vector but show off Catch2 features
#include "../my_deque/my_deque.h"
         "
#include "../my_vector/my_vector.h"
         "
#include <clocale>
#include <color_macros.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

// template <typename T>
// void check_node(const T &node, bool expected_in_use, T *expected_next) {
//   REQUIRE(node.in_use == expected_in_use);
//   REQUIRE(node.next_free == expected_next);
// }
//
// template <typename T>
// void check_pool_state(const ObjectPool<T> &pool, size_t expected_used) {
//   REQUIRE(pool.num_used() == expected_used);
//   REQUIRE(verify_pool(pool));
// }

// Things to test
// - Invariants - sizes, list integrity
// - state changes - acquire, release
// - edge cases and boundary conditions
// - errors/misuse - invalid inputs, double release

template <typename T> bool verify_pool_invariants(const ObjectPool<T> &pool) {
  CHECK(check_freelist_integrity(pool));
  return pool.num_used() + pool.num_free() == pool.num_allocated();
}

CATCH_REGISTER_TAG_ALIAS("[@PoolTemplate]", "[ObjectPool][Object]~[.]");
// TEST_CASE("Correct Object Pool Size", "[ObjectPool]") {

using MyTypes = std::tuple<int, char, float>;
TEMPLATE_LIST_TEST_CASE("Test w/ above types", "[template][list]", MyTypes) {}

TEMPLATE_TEST_CASE("ObjectPool Test", "[ObjectPool]", Object /*, int */) {
  // this is the setup section - for each section, this code is executed anew
  // CHECK continues running on failure, REQUIRE halts program on failure
  // SECTION aliases: SCENARIO, GIVEN, WHEN, THEN, AND_GIVEN, AND_WHEN, AND_THEN

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
    verify_pool_invariants(pool);
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
  SECTION("Partial Initialization") {
    size_t u_pool_slots = 10;
    ObjectPool<TestType> u_pool(u_pool_slots);
    // auto data = u_pool.data();

    // CHECK(u_pool.free_objects == nullptr);
    u_pool.initialize(5);
    // CHECK(u_pool.free_objects == &data[0]);
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

  obj = pool.acquire("charlie", 7); // acquire third
  CHECK(obj->next_free == nullptr);

  CHECK(pool.is_full() == true);
  CHECK(pool.num_used() == pool_slots);

  // test acquiring when pool is full
  obj = pool.acquire("steve", 6);
  CHECK(obj == nullptr);
  REQUIRE(check_freelist_integrity(pool));

  SECTION("ObjectPool release") {
    obj = &data[1];

    pool.release(obj);
    CHECK(pool.is_full() == false);
    CHECK(pool.num_used() == pool_slots - 1);

    obj = pool.acquire("blerbera", 321);
    CHECK(pool.is_full() == true);

    pool.release_all();
    CHECK(pool.is_empty() == true);
    REQUIRE(check_freelist_integrity(pool));
  }
}

TEMPLATE_TEST_CASE("ObjectPool free list integrity", "[ObjectPool]",
                   Object /*, int */) {
  ObjectPool<TestType> pool(16, true);

  SECTION("initial integrity") { REQUIRE(check_freelist_integrity(pool)); }

  SECTION("after acquire/release sequence") {
    auto *a = pool.acquire();
    auto *b = pool.acquire();
    pool.release(a);
    pool.release(b);
    REQUIRE(check_freelist_integrity(pool));
  }

  SECTION("detect double release") {

    auto *a = pool.acquire();
    pool.release(a);
    // intentional misuse - handled by release() defensively
    // pool.release(a);
    //
    REQUIRE(check_freelist_integrity(pool));
  }
}
