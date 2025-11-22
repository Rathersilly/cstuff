#include "array_queue.h"
#include <array>
#include <iostream>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("ArrayQueue", "[queue]") {
  int array_size = 3;
  ArrayQueue queue(array_size);
  CHECK_NOTHROW(queue.pop());
  CHECK(queue.empty() == true);
  CHECK(queue.full() == false);

  SECTION("push until full") {
    queue.push(0);
    CHECK(queue.front() == 0);
    CHECK(queue.back() == 0);
    CHECK(queue.empty() == false);

    queue.push(1);
    queue.push(2); // queue now full
    CHECK(queue.front() == 0);
    CHECK(queue.back() == 2);
    CHECK(queue.empty() == false);
    CHECK(queue.full() == true);

    queue.push(3); // push when queue full
    CHECK(queue.front() == 0);
    CHECK(queue.back() == 2);
    CHECK(queue.empty() == false);
    CHECK(queue.full() == true);
  }

  SECTION("pop until empty") {
    queue.push(0);
    queue.push(1);
    queue.push(2);
    queue.pop();
    CHECK(queue.front() == 1);
    CHECK(queue.back() == 2);
    queue.pop();
    CHECK(queue.front() == 2);
    CHECK(queue.back() == 2);
    CHECK(queue.empty() == false);
    queue.pop();
    CHECK(queue.empty() == true);
  }

  SECTION("front index > back index") {
    queue.push(0);
    queue.push(1);
    queue.push(2);
    queue.pop();

    queue.push(3);
    CHECK(queue.full() == true);
    // now front index == 1,back index == 0

    for (int i = 4; i < array_size * 3; ++i) {
      queue.pop();
      queue.push(i);
      CHECK(queue.front() == i - 2);
      CHECK(queue.back() == i);
    }
  }
  SECTION("get vector queue (vector of queue in order)") {
    queue.push(0);
    queue.push(1);
    queue.push(2);

    std::vector vec = queue.get_vector();
    std::vector reference{0, 1, 2};
    for (int i = 0; i < array_size; ++i) {
      CHECK(vec[i] == reference[i]);
    }

    queue.pop();
    queue.push(3);
    vec = queue.get_vector();
    reference = {1, 2, 3};
    for (int i = 0; i < array_size; ++i) {
      CHECK(vec[i] == reference[i]);
    }
  }

  SECTION("displaying queue(actual and underlying)") {
    queue.push(0);
    queue.push(1);
    queue.push(2);

    queue.display();     // [0, 1, 2]
    queue.display_raw(); // [0, 1, 2]

    queue.pop();
    queue.push(3);

    queue.display();                          // [1, 2, 3]
    queue.display_raw();                      // [3, 1, 2]
    std::vector vec = queue.get_vector_raw(); // [3, 1, 2]

    for (auto &n : vec) {
      cout << n << " ";
    }
    cout << endl;

    queue.pop();

    queue.display_raw();          // [3, 1, 2] still
    vec = queue.get_vector_raw(); // [3, 1, 2] still

    for (auto &n : vec) {
      cout << n << " ";
    }
    cout << endl;
  }
}
