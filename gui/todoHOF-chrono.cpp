// Clocks and Sleeping - mostly from cppref
#include <chrono>
#include <iostream>
#include <ratio>
#include <thread>
#include <typeinfo>
using namespace std;
using namespace std::chrono;
using std::chrono::operator""ms;      // redundant with ^^
using namespace std::chrono_literals; // also redundant

auto now() { return std::chrono::steady_clock::now(); }

auto awake_time() { return now() + 200ms; }

int main(int argc, char *argv[]) {

  // std::chrono::duration helper types
  // duration literals: h, min, s, ms, us, ns
  std::chrono::milliseconds some_frames(1000s / 60s);
  std::chrono::seconds some_seconds = 100s;
  auto some_nanoseconds = 100ns;
  auto dur = 10min;

  // now() returns std::chrono::time_point
  auto start = std::chrono::steady_clock::now();

  // how to sleep:
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  std::this_thread::sleep_until(awake_time());
  std::this_thread::sleep_until(now() + 200ms);

  auto end = std::chrono::steady_clock::now();

  //  *** std::chrono::duration ***
  // std::chrono::duration = # of ticks
  // duration can be converted to units with duration_cast
  // duration can be printed with .count()

  // time_point - time_point = duration
  // this is explicit duration type - feel free to use auto:
  // auto diff = end - start;
  const std::chrono::duration<double> diff = end - start;

  // time_since_epoch() converts time_point to duration
  // get the duration since epoch
  auto start_time_since_epoch = start.time_since_epoch();

  std::cout << "Time since epoch: "
            << std::chrono::duration_cast<std::chrono::seconds>(
                   start_time_since_epoch)
                   .count()
            << " seconds" << std::endl;

  cout << typeid(start).name() << endl; // std::chrono::time_point

  cout << "diff.count()" << diff.count() << endl;

  // use duration_cast to convert ticks to seconds/milliseconds etc
  cout << std::chrono::duration_cast<std::chrono::seconds>(diff).count()
       << endl;
  ;
  cout << std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count()
       << endl;

  // from cppref
  std::chrono::seconds halfmin = 30s;
  std::cout << "Half a minute is " << halfmin.count() << " seconds.\n";
  cout << "A minute and a second is " << (1min + 1s).count() << " seconds.\n";

  std::cout << "Half a minute is " << halfmin.count() << " seconds.\n";

  std::chrono::duration<double> moment = 0.1s;
  std::cout
      << "A moment is " << moment.count() << " seconds"
      << " ("
      << std::chrono::duration_cast<std::chrono::milliseconds>(moment).count()
      << " milliseconds).\n"
      << "And thrice as much is "
      << std::chrono::duration_cast<std::chrono::milliseconds>(moment + 0.2s)
             .count()
      << " milliseconds.\n";
  std::cout << "Time since epoch: "
            << std::chrono::duration_cast<std::chrono::seconds>(
                   start_time_since_epoch)
                   .count()
            << " seconds" << std::endl;
  return 0;
}
