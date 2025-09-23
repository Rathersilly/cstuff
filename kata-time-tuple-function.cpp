// just a kata file with simple benchmarking, tuples, std::function, time
#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
using namespace std;

mt19937 mt{random_device{}()};

namespace timer {
using myclock = std::chrono::steady_clock;
inline auto now_ns() {
  return std::chrono::time_point_cast<std::chrono::nanoseconds>(myclock::now());
}

// never ended up using these
using nanoseconds = decltype(now_ns());
using dtime = decltype(now_ns() - now_ns());

} // namespace timer

using TestResultTuple =
    std::tuple<std::string, std::function<string(string)>,
               std::chrono::nanoseconds, std::chrono::nanoseconds,
               std::chrono::nanoseconds>;

struct TestResult {
  std::string name;
  std::function<string(string)> fun;
  std::chrono::nanoseconds avg_time;
  std::chrono::nanoseconds max_time;
  std::chrono::nanoseconds min_time;
};

// another newb on reddit made this function that scrambles a string.
// their original had flaws (On^2, srand,)
string distortorig(string s) {
  srand(time(0));
  while (!s.empty()) {
    int c = rand() % s.length();
    cout << s[c];
    s.erase(s.begin() + c);
  }
  return "sup"; // just returning a random string to make function sigs match
}

string distortcout(string s) {
  string result{};
  while (!s.empty()) {
    int c = mt() % s.length();
    cout << s[c];
    s.erase(s.begin() + c);
  }
  return result;
}

string distortreturn(string s) {
  string result{};
  while (!s.empty()) {
    int c = mt() % s.length();
    result.push_back(s[c]);
    s.erase(s.begin() + c);
  }
  return result;
}

string distortbest(string s) {
  string result{};
  result.reserve(s.size());

  while (!s.empty()) {
    int c = mt() % s.length(); // c is random index
    result.push_back(s[c]);    // add that char to result
    std::swap(s[c], s.back());
    s.pop_back();
  }
  return result;
}

void test_distort_tuple(string test_string, TestResultTuple &final_result,
                        int warmup_runs = 10, int runs = 200) {

  auto &[name, fun, avg, max, min] = final_result;
  vector<timer::dtime> run_results{};
  run_results.reserve(runs);

  for (int i = 0; i < warmup_runs; ++i) {
    fun(test_string);
  }
  for (int i = 0; i < runs; ++i) {
    auto start = timer::now_ns();
    fun(test_string);
    auto dur = timer::now_ns() - start;
    run_results.push_back(dur);
  }
  auto total_duration =
      std::accumulate(run_results.begin(), run_results.end(), timer::dtime{0});
  avg = total_duration / runs;
  max = *std::max_element(run_results.begin(), run_results.end());
  min = *std::min_element(run_results.begin(), run_results.end());
}

void test_distort(string test_string, TestResult &result, int warmup_runs = 10,
                  int runs = 200) {

  vector<timer::dtime> run_results{};
  run_results.reserve(runs);

  for (int i = 0; i < warmup_runs; ++i) {
    result.fun(test_string);
  }
  for (int i = 0; i < runs; ++i) {
    auto start = timer::now_ns();
    result.fun(test_string);
    auto dur = timer::now_ns() - start;
    run_results.push_back(dur);
  }
  auto total_duration =
      std::accumulate(run_results.begin(), run_results.end(), timer::dtime{0});
  result.avg_time = total_duration / runs;
  result.max_time = *std::max_element(run_results.begin(), run_results.end());
  result.min_time = *std::min_element(run_results.begin(), run_results.end());
}

void print_results(const TestResultTuple &result) {
  auto [name, fun, avg_time, max_time, min_time] = result;

  cout << '\n'
       << setw(20) << name << setw(10) << avg_time.count() << setw(10)
       << max_time.count() << setw(10) << min_time.count() << endl;
}

void print_results(const TestResult &result) {

  cout << setw(20) << result.name << setw(10) << result.avg_time.count()
       << setw(10) << result.max_time.count() << setw(10)
       << result.min_time.count() << endl;
}

int main() {
  TestResult result{"orig", distortorig};
  string test_string = "donkey";

  cout << '\n'
       << setw(20) << "name" << setw(10) << "avg time" << setw(10) << "max time"
       << setw(10) << "min time" << endl;

  // redirecting stdout
  std::ofstream nullout("/dev/null"); // open /dev/null
  auto old_buf = std::cout.rdbuf();   // save old buffer
  std::cout.rdbuf(nullout.rdbuf());   // redirect cout
  std::cout << "This goes nowhere\n"; // still "costs time" to execute
  test_distort(test_string, result);
  std::cout.rdbuf(old_buf); // restore original buffer
  print_results(result);

  result = TestResult{"distort cout", distortcout};
  old_buf = std::cout.rdbuf();      // save old buffer
  std::cout.rdbuf(nullout.rdbuf()); // redirect cout
  test_distort("donkey", result);
  std::cout.rdbuf(old_buf); // restore original buffer
  print_results(result);

  result = TestResult{"distort return", distortreturn};
  test_distort("donkey", result);
  print_results(result);

  result = TestResult{"distort best", distortbest};
  test_distort("donkey", result);
  print_results(result);

  TestResultTuple result_tuple{"distort best", distortbest, {}, {}, {}};
  test_distort_tuple("donkey", result_tuple);
  print_results(result_tuple);
}
