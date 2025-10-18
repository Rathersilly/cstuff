#include <fmt/base.h>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/ranges.h>
#include <iostream>

using namespace std;

int main() {
  fmt::print("Hello, world!\n");
  // Formatting
  // fmt::format(string) → std::string
  // fmt::format(format-string, arguments...) → std::string
  // fmt::format_to(@output, format-string, arguments...)

  auto str = fmt::format("in {}s\n", 47);
  std::cout << str; // in 47s

  // Printing
  // fmt::print(string)
  // fmt::print(format-string, arguments...)
  // fmt::print(file, format-string, arguments...)

  fmt::print("in {}s\n", 47);             // in 47s
  fmt::print(stderr, "error: {}\n", 404); // error: 404

  // Format a string(run)
  std::string s = fmt::format("The answer is {}.", 42);
  // s == "The answer is 42."

  // Format a string using positional arguments(run)
  std::string s2 = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
  // s2 == "I'd rather be happy than right."

  // Print dates and times(run)
  auto now = std::chrono::system_clock::now();
  fmt::print("Date and time: {}\n", now);
  fmt::print("Time: {:%H:%M}\n", now);
  // Output:
  //
  // Date and time: 2023-12-26 19:10:31.557195597
  // Time: 19:10

  // Print a container (requires #include <fmt/ranges.h>)
  std::vector<int> v = {1, 2, 3};
  fmt::print("{}\n", v);
  // Output :
  //     [ 1, 2, 3 ]

  // Print with colors and text styles
  fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, "Hello, {}!\n",
             "world");
  fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
                 fmt::emphasis::underline,
             "Olá, {}!\n", "Mundo");
  fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic, "你好{}！\n",
             "世界");
  fmt::print("hi\n");
}
