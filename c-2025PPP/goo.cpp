#include <exception>
#include <iostream>
#include <random>
#include <sstream>

class MyError : public std::logic_error {
  std::string full_msg;

public:
  MyError(const char *msg, const char *file, int line)
      : std::logic_error(msg),
        full_msg(std::string(file) + ":" + std::to_string(line) + " - " + msg) {
  }

  const char *what() const noexcept override { return full_msg.c_str(); }
};

int main(int argc, char *argv[]) { return 0; }
