#include <algorithm>
#include <numeric>
#define TEST
#include "my_packedstringarray.h"
#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ostream.h> // to print to std::cerr
#include <iostream>
using std::vector, std::string;

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
using fmt::print;

TEST_CASE("Constructor", "[psa]") {
  PackedStringArray arr(64);
  auto size = arr.size();
  auto indices = arr.indices();
  CHECK(arr.size() == 0);
  CHECK(arr.capacity() == 64);

  SECTION("push_back") {
    vector<string> strings{"hello", "there", "old", "pal"};
    size_t strings_bytes =
        std::accumulate(strings.begin(), strings.end(), (size_t)0,
                        [](size_t n, const string &s) { return s.size() + n; });

    auto strings_joined =
        std::accumulate(strings.begin(), strings.end(), ""s,
                        [](const string &a, const string &b) { return a + b; });
    arr.push_back(strings[0]);
    CHECK(arr.bytes_used() == strings[0].size());
    CHECK(arr.bytes_free() == arr.capacity() - strings[0].size());
    CHECK(arr.to_str() == strings[0]);
    arr.print_all();

    PackedStringArray arr2(64);
    for (auto &s : strings)
      arr2.push_back(s);

    CHECK(arr2.bytes_used() == strings_bytes);
    CHECK(arr2.bytes_used() == strings_bytes);
    CHECK(arr2.to_str() == strings_joined);
    // arr.print_all();
    SECTION("operator[]") {
      vector<string> strings{"hello", "there", "old", "pal"};

      CHECK(strings[0][1] == 'e');
    }
    SECTION("push_back limits") {}
  }
  SECTION("sadf") {}
}
