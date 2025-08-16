// Google Benchmark framework demo
// CPPCon 2017 Chandler Carruth (Google C++ Dude)
// https://www.youtube.com/watch?v=2EWejmkKlxs
#include "my_helpers.h"
#include <benchmark/benchmark.h>
#include <limits>
#include <string>
#include <vector>

template <typename T> std::vector<T> RNG(int min, int max, int count) {
  std::uniform_int_distribution<> range{min, max};
  std::vector<T> res;
  res.reserve(count);
  for (int i = 0; i < count; ++i)
    res.push_back(range(mt));
  return res;
}

// Randomly access a vector and see the bytes/second processed
// vs vector size.  We see dropoffs of performance at each cache tier.
static void cacheBench(benchmark::State &s) {
  int bytes = 1 << s.range(0);
  // Compute how many elements we can fit into this many bytes given that we
  // need 2x to represent both data and indices into the data
  int count = (bytes / sizeof(int)) / 2;
  std::vector<int> v;
  for (auto i : RNG<int>(std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::max(), count))
    v.push_back(i);
  std::vector<int> indices;
  for (auto i : RNG<int>(0, count, count))
    indices.push_back(i);
  while (s.KeepRunning()) {
    long sum = 0;
    for (int i : indices)
      sum += v[i];
    benchmark::DoNotOptimize(sum);
  }

  s.SetBytesProcessed(long(s.iterations() * long(bytes)));
  s.SetLabel(std::to_string(bytes / 1024) + "kb");
}

static void clampBench(benchmark::State &s) {
  int size = s.range(0);
  std::vector<int> v;
  for (auto i : RNG<int>(0, std::numeric_limits<int>::max(), size))
    v.push_back(i);

#pragma clang loop vectorize(disable) interleave(disable) unroll(disable)
  while (s.KeepRunning()) {
    for (int &i : v) {
      i = i > 255 ? 255 : i;
      benchmark::DoNotOptimize(v);
    }

    s.SetItemsProcessed(long(s.iterations()) * long(v.size()));
  }
}
static void BM_StringCompare(benchmark::State &state) {
  std::string s1(state.range(0), '-');
  std::string s2(state.range(0), '-');
  for (auto _ : state) {
    auto comparison_result = s1.compare(s2);
    benchmark::DoNotOptimize(comparison_result);
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_StringCompare)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 18)
    ->Complexity();
BENCHMARK(BM_StringCompare)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 18)
    ->Complexity(benchmark::oN);

// BENCHMARK(cacheBench)->DenseRange(13, 26)->ReportAggregatesOnly(true);
// BENCHMARK(clampBench)->Range(1 << 10, 1 << 20)->ReportAggregatesOnly(true);
BENCHMARK_MAIN();
