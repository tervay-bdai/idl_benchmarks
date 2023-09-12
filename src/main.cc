#include <iostream>

#include "benchmark/benchmark.h"
#include "src/benchmark_fbs.h"

static void BM_flatbufSimple(benchmark::State &state) {
  FbsBenchmarkable fbs;

  for (auto _ : state) {
    fbs.serialize();
  }
}

static void BM_gLogAdvanced(benchmark::State &state) {
  for (auto _ : state) {
  }
}

int main(int argc, char **argv) {
  benchmark::RegisterBenchmark("BM_flatbufSimple", BM_flatbufSimple);
  benchmark::RegisterBenchmark("gLogAdvanced", BM_gLogAdvanced);
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
}