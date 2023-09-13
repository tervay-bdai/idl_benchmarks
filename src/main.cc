#include <iostream>

#include "benchmark/benchmark.h"
#include "src/benchmark_fbs.h"
#include "src/benchmark_nanopb.h"
#include "src/benchmark_proto2.h"
#include "src/benchmark_proto3.h"
#include "src/benchmark_proto3_arena.h"
#include "src/benchmark_ros2.h"
#include "src/benchmark_upb.h"

inline constexpr size_t num_cycle_tests[] = {1, 10, 100};

static void CustomArguments(benchmark::internal::Benchmark *b) {
  for (auto &x : num_cycle_tests) {
    b->Arg(x);
  }
}

#define ADD_BM(name, benchmarkable_type)                                       \
  template <class... Args>                                                     \
  static void BM_##name(benchmark::State &state, Args &&...args) {             \
    benchmarkable_type benchmarkable;                                          \
    for (auto _ : state) {                                                     \
      benchmarkable.serialize(benchmarkable.makeMessage(state.range(0)));      \
    }                                                                          \
  }                                                                            \
                                                                               \
  BENCHMARK(BM_##name)                                                         \
      ->ComputeStatistics("max",                                               \
                          [](const std::vector<double> &v) -> double {         \
                            return *(                                          \
                                std::max_element(std::begin(v), std::end(v))); \
                          })                                                   \
      ->ComputeStatistics("min",                                               \
                          [](const std::vector<double> &v) -> double {         \
                            return *(                                          \
                                std::min_element(std::begin(v), std::end(v))); \
                          })                                                   \
      ->Apply(CustomArguments);

ADD_BM(proto2, Proto2Benchmarkable);
ADD_BM(proto3, Proto3Benchmarkable);
ADD_BM(proto3_arena, Proto3ArenaBenchmarkable);
ADD_BM(upb, UpbBenchmarkable);
ADD_BM(nanopb, NanoPbBenchmarkable);
ADD_BM(flatbuf, FbsBenchmarkable);
ADD_BM(ros2, Ros2Benchmarkable);

BENCHMARK_MAIN();
