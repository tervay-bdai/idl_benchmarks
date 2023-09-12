#include <iostream>

#include "benchmark/benchmark.h"
#include "src/benchmark_fbs.h"
#include "src/benchmark_nanopb.h"
#include "src/benchmark_proto2.h"
#include "src/benchmark_proto3.h"
#include "src/benchmark_upb.h"

static void BM_flatbuf(benchmark::State &state) {
  FbsBenchmarkable fbs;

  for (auto _ : state) {
    fbs.serialize();
  }
}

static void BM_proto2(benchmark::State &state) {
  Proto2Benchmarkable pb2;
  for (auto _ : state) {
    pb2.serialize();
  }
}

static void BM_proto3(benchmark::State &state) {
  Proto3Benchmarkable pb3;
  for (auto _ : state) {
    pb3.serialize();
  }
}

static void BM_nanopb(benchmark::State &state) {
  NanoPbBenchmarkable npb;
  for (auto _ : state) {
    npb.serialize();
  }
}

static void BM_upb(benchmark::State &state) {
  UpbBenchmarkable upb;
  for (auto _ : state) {
    upb.serialize();
  }
}

BENCHMARK(BM_flatbuf)
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("min", [](const std::vector<double> &v) -> double {
      return *(std::min_element(std::begin(v), std::end(v)));
    });
BENCHMARK(BM_proto2)
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("min", [](const std::vector<double> &v) -> double {
      return *(std::min_element(std::begin(v), std::end(v)));
    });
BENCHMARK(BM_proto3)
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("min", [](const std::vector<double> &v) -> double {
      return *(std::min_element(std::begin(v), std::end(v)));
    });
BENCHMARK(BM_nanopb)
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("min", [](const std::vector<double> &v) -> double {
      return *(std::min_element(std::begin(v), std::end(v)));
    });
BENCHMARK(BM_upb)
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("min", [](const std::vector<double> &v) -> double {
      return *(std::min_element(std::begin(v), std::end(v)));
    });

BENCHMARK_MAIN();
