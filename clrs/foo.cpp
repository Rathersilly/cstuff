#include <iostream>
using namespace std;

struct S {
  int arr[10];
};
int main(int argc, char *argv[]) {

  void *chunk = malloc(32);
  auto addr = [](void *ptr) {
    return static_cast<void *>(static_cast<char *>(ptr));
  };
  auto addr2 = [](void *ptr, size_t offset = 0) -> void * {
    return static_cast<void *>(static_cast<char *>(ptr) + offset);
  };
  cout << addr(chunk) << " " << addr(chunk) << endl;
  cout << addr2(chunk, 0) << " " << addr2(chunk, 10) << endl;
  cout << addr2(chunk, 0) << " " << addr2(chunk, 31) << endl;
  cout << addr2(chunk, 0) << " " << addr2(chunk, 32) << endl;
  cout << (static_cast<char *>(chunk) + 10) << endl;
  int *a;
  return 0;
}
