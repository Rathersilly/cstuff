#include <iostream>

int main(int argc, char *argv[]) {
  try {
    throw std::exception(); // exception is the superclass of runtime_error.
                            // exception() can't take a string argument
    throw std::runtime_error("HI");
  } catch (std::runtime_error e) {
    std::cout << "runtime error found: " << e.what()
              << std::endl; // e.what() contains "HI"

    return 0;
  } catch (std::exception e) {
    std::cout << "exception found: " << e.what()
              << std::endl; // e.what() will always just say "std::exception"
  } catch (...) {
    std::cout << "exception found: "
              << std::endl; // e.what() will always just say "std::exception"
  }
}

