#include <iostream>

#include "benchmark/benchmark.h"
#include "src/benchmark_fbs.h"
#include "src/benchmark_nanopb.h"
#include "src/benchmark_proto2.h"
#include "src/benchmark_proto3.h"

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

BENCHMARK(BM_flatbuf);
BENCHMARK(BM_proto2);
BENCHMARK(BM_proto3);
BENCHMARK(BM_nanopb);
BENCHMARK_MAIN();
