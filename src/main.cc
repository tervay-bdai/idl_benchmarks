#include <iostream>

#include "benchmark/benchmark.h"
#include "src/benchmark_fbs.h"
// #include "src/benchmark_nanopb.h"
#include "src/benchmark_proto2.h"
#include "src/benchmark_proto3.h"
#include "src/benchmark_upb.h"

#define ADD_BM(name, benchmarkable_type)                                       \
  static void BM_##name(benchmark::State &state) {                             \
    benchmarkable_type benchmarkable;                                          \
    for (auto _ : state) {                                                     \
      benchmarkable.serialize();                                               \
    }                                                                          \
  }                                                                            \
                                                                               \
  BENCHMARK(BM_##name)                                                         \
      ->ComputeStatistics("max",                                               \
                          [](const std::vector<double> &v) -> double {         \
                            return *(                                          \
                                std::max_element(std::begin(v), std::end(v))); \
                          })                                                   \
      ->ComputeStatistics("min", [](const std::vector<double> &v) -> double {  \
        return *(std::min_element(std::begin(v), std::end(v)));                \
      });

ADD_BM(flatbuf, FbsBenchmarkable);
ADD_BM(proto2, Proto2Benchmarkable);
ADD_BM(proto3, Proto3Benchmarkable);
// ADD_BM(nanopb, NanoPbBenchmarkable);
ADD_BM(upb, UpbBenchmarkable);

BENCHMARK_MAIN();
