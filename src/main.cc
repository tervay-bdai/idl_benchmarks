#include <iostream>

#include "benchmark/benchmark.h"
#include "src/benchmark_fbs.h"
#include "src/benchmark_proto2.h"

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

int main(int argc, char **argv) {
  benchmark::RegisterBenchmark("BM_flatbuf", BM_flatbuf);
  benchmark::RegisterBenchmark("BM_proto2", BM_proto2);
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
}