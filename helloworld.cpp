#include <iostream>

int main(int argc, char *argv[]) {

  class Hello {
  public:
    Hello();
    Hello(Hello &&) = default;
    Hello(const Hello &) = default;
    Hello &operator=(Hello &&) = default;
    Hello &operator=(const Hello &) = default;
    ~Hello();
    void add(int a, int b);

  private:
  };

  Hello::Hello() {}

  Hello::~Hello() {}
  Hello::add(int a, int b) { return a + b; }

  std::cout << "Hello World" << std::endl;
  cout hi;
  cout hi;
  cout hi;
  cout hi;
  Hello asdf;
  asdf.add(1, 2);
  return 0;
}
