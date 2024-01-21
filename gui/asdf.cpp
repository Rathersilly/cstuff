#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

int main(int argc, char *argv[]) {

  auto start = std::chrono::steady_clock::now();
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  auto end = std::chrono::steady_clock::now();
  /* auto diff = end_time - start_time; */
  const std::chrono::duration<double> diff = end - start;
  cout << diff.count();
  cout << diff.count() << endl;

  cout << std::chrono::duration_cast<std::chrono::seconds>(diff).count()
       << endl;
  ;
  cout << std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count()
       << endl;

  return 0;
}
