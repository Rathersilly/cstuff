// Clocks and Sleeping - mostly from cppref
#include <chrono>
#include <iostream>
#include <ratio>
#include <thread>
using namespace std;
using namespace std::chrono;
// can be particular with using:
// using std::chrono::operator""ms;
// using namespace std::chrono_literals;
// using std::chrono::steady_clock, std::chrono::duration;

auto now() { return std::chrono::steady_clock::now(); }
auto awake_time() { return now() + 20ms; }

int main(int argc, char *argv[]) {

  // Clocks
  // They are classes with static functions - dont need to be instantiated
  // Types of Clocks
  // std::chrono::high_resolution_clock  // has now() -> time_point
  // std::chrono::steady_clock           // has now() -> time_point
  // std::chrono::system_clock           // has now() -> time_point AND:
  //                                       to_time_t() -> std::time_t
  //                                       from_time_t() -> std::time_t

  time_point<steady_clock> steady_now = steady_clock::now();
  cout << "steady now: " << steady_now.time_since_epoch().count() << endl;

  time_point<high_resolution_clock> high_resolution_now =
      high_resolution_clock::now();
  cout << "high_resolution now: "
       << high_resolution_now.time_since_epoch().count() << endl;

  // *** Time Point ***
  // template<class Clock, class Duration = class Clock::Duration>
  // class time_point
  //
  // time points contain a time_since_epoch() function
  // and arithmetic functions

  // *** Duration ***
  // template< class Rep, class Period = std::ratio<1>> class duration;
  //
  // Rep is numeric type that holds ticks
  // Period is fraction of second per tick
  // eg duration<double,std::micro> foo
  //
  // duration<long long,std::nano> asdf = 100ns;
  //   is equivalent to
  // auto foo = 100ns;
  // (std::nano == std::ratio<1,1'000'000'000>')
  //
  // time_point - time_point = duration
  // duration can be converted to units with duration_cast
  // duration ticks can be printed with .count()

  // *** Examples ***

  // time_since_epoch() converts time_point to duration
  // count() converts duration to ticks
  auto start_time_since_epoch = system_clock::now().time_since_epoch();

  std::cout << "Time since epoch: "
            << duration_cast<seconds>(start_time_since_epoch).count()
            << " seconds" << std::endl;

  // Measuring time:
  auto start = steady_clock::now(); // create a time_point

  // how to sleep:
  std::this_thread::sleep_for(milliseconds(10));
  std::this_thread::sleep_until(awake_time());
  std::this_thread::sleep_until(now() + 20ms);

  auto end = steady_clock::now();

  auto diff_auto = end - start; // auto is duration<long long,std::ratio<1>>
  const duration<double> diff_double = end - start;
  cout << "diff_auto.count(): " << diff_auto.count() << "ns" << endl;
  cout << "diff_double.count(): " << diff_double.count() << "s" << endl;

  // use duration_cast to convert ticks to seconds/milliseconds etc
  cout << "diff_double.count() in ms: "
       << duration_cast<milliseconds>(diff_double).count() << endl;

  // Arithmetic
  auto some_time = 10s;
  some_time += 10min; // 610s

  // duration_cast to convert to years
  constexpr int seconds_per_year = 60 * 60 * 24 * 365; // ratio needs constexpr
  duration<double, ratio<seconds_per_year>> years_since_epoch =
      system_clock::now().time_since_epoch();
  cout << "years since epoch: " << years_since_epoch.count() << endl;

  // duration_cast to convert to microfortnights
  using microfortnights =
      duration<double,
               ratio_multiply<ratio_multiply<ratio<2>, weeks::period>, micro>>;
  microfortnights d = 1s;
  cout << "1s is " << d.count() << " microfortnights" << endl;
  // alternatively, directly use duration constructor:
  cout << "1s is " << microfortnights(1s).count() << " microfortnights" << endl;

  // can leave off the count() to print: 55.7785[31536000]s
  cout << "years since epoch: " << years_since_epoch << endl;

  // std::chrono::duration helper types:
  // std::chrono::years, months, weeks, days, hours, minutes, seconds,
  //   milliseconds, microseconds, nanoseconds
  //
  // std::chrono::duration literals: ns, us, ms, s, min, h

  // seconds is duration<long long, std::ratio<1>>
  // millileconds is duration<long long, std::milli>
  std::chrono::seconds some_seconds = 100s;
  std::chrono::milliseconds some_frames(1000s / 60s); // truncates

  auto some_nanoseconds = 100ns;
  auto some_minutes = 10min;

  // if we prefer fractional:
  duration<double, milli> ms_long = 100ms; // count() == 100

  // and in fraction of seconds(default is std::ratio<1>):
  duration<double> sec_fraction = 100ms; // count() == 0.1

  // to query the ratio of a duration:
  // nanoseconds::period is a std::ratio
  cout << "ratio of seconds to nanoseconds: ";
  cout << decltype(some_nanoseconds)::period::num << "/"
       << decltype(some_nanoseconds)::period::den << endl;

  // TODO: system_clock section
  auto current_time = system_clock::now();
  cout << std::chrono::current_zone()->to_local(current_time) << endl;
  return 0;
}
