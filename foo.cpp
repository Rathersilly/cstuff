#include <algorithm>
#include <chrono>
#include <deque>
#include <iostream>
#include <typeinfo>
using namespace std;
// A function to demonstrate using a deque as a sliding
// window over data.
void processInSlidingWindow(const std::deque<int> &data, size_t windowSize) {
  for (size_t i = 0; i <= data.size() - windowSize; ++i) {
    int sum = 0;
    for (size_t j = i; j < i + windowSize; ++j) {
      sum += data[j];
    }
    std::cout << "Average of window starting at index " << i << ": "
              << static_cast<double>(sum) / windowSize << "\n";
  }
}
int main() {
  using namespace std::chrono;
  auto clock = steady_clock{};
  // auto foo = clock.now();
  // auto goo = foo.time_since_epoch();
  // cout << typeid(foo).name() << endl;
  // cout << typeid(goo).name() << endl;
  // cout << goo.count();

  auto asdf = 100ns;
  auto start = steady_clock::now();
  cout << typeid(asdf).name() << endl;
  cout << asdf.count() << endl;
  ;
  auto end = steady_clock::now();
  auto diff = end - start;
  cout << typeid(diff).name() << endl;
  cout << diff.count() << endl;

  auto steady = steady_clock::now();
  cout << typeid(steady).name() << endl;
  cout << steady.time_since_epoch().count() << endl;

  auto hr = high_resolution_clock::now();
  cout << typeid(hr).name() << endl;
  cout << hr.time_since_epoch().count() << endl;
  auto system = system_clock::now();
  cout << typeid(system).name() << endl;
  cout << system.time_since_epoch().count() << endl;
  auto dur = duration_cast<seconds>(system.time_since_epoch());
  cout << dur / 60 / 60 / 24 / 365 << endl;

  cout << decltype(diff)::period::num << endl;
  cout << decltype(diff)::period::den << endl;
  auto bleh = 100ms;
  duration<double> dub = bleh;
  cout << dub.count() << endl;
  ;
  //   duration_cast<seconds> → truncates to integer seconds.
  // duration<double> → allows fractional seconds.
  duration<double> wert = 100ms;
  cout << wert.count() << endl;

  cout << decltype(start)::period::num << "/" << decltype(start)::period::den
       << endl;
};
