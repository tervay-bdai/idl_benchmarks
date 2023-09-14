#include <iostream>

#include "benchmark/benchmark.h"
#include "rclcpp/rclcpp.hpp"
#include "src/benchmark_capnp.h"
#include "src/benchmark_fbs.h"
#include "src/benchmark_nanopb.h"
#include "src/benchmark_proto2.h"
#include "src/benchmark_proto3.h"
#include "src/benchmark_proto3_arena.h"
#include "src/benchmark_ros2.h"
#include "src/benchmark_upb.h"

double calculateQ1(const std::vector<double> &v) {
  std::vector<double> sorted = v;
  std::sort(sorted.begin(), sorted.end());

  size_t n = sorted.size();
  size_t q1_index = n / 4;
  double q1 = 0.0;

  if (n % 4 == 0) {
    q1 = (sorted[q1_index - 1] + sorted[q1_index]) / 2.0;
  } else {
    q1 = sorted[q1_index];
  }

  return q1;
}

double calculateQ3(const std::vector<double> &v) {
  std::vector<double> sorted = v;
  std::sort(sorted.begin(), sorted.end());

  size_t n = sorted.size();
  size_t q3_index = 3 * n / 4;
  double q3 = 0.0;

  if (n % 4 == 0) {
    q3 = (sorted[q3_index - 1] + sorted[q3_index]) / 2.0;
  } else {
    q3 = sorted[q3_index];
  }

  return q3;
}

inline constexpr size_t num_cycle_tests[] = {1, 10, 100, 1000, 2500, 5000};

static void CustomArguments(benchmark::internal::Benchmark *b) {
  for (auto &x : num_cycle_tests) {
    b->Arg(x);
  }
}

#define CREATE_BM(name)                                                        \
  BENCHMARK(name)                                                              \
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
      ->ComputeStatistics("q1",                                                \
                          [](const std::vector<double> &v) -> double {         \
                            return calculateQ1(v);                             \
                          })                                                   \
      ->ComputeStatistics("q3",                                                \
                          [](const std::vector<double> &v) -> double {         \
                            return calculateQ3(v);                             \
                          })                                                   \
      ->Unit(benchmark::kMicrosecond)                                          \
      ->Apply(CustomArguments);

#define ADD_BM_TMPL(name, benchmarkable_type, tmpl)                            \
  template <class... Args>                                                     \
  static void BM_##name(benchmark::State &state, Args &&...args) {             \
    MinimalPublisher<tmpl> publisher;                                          \
    benchmarkable_type benchmarkable(&publisher);                              \
    for (auto _ : state) {                                                     \
      benchmarkable.serialize(benchmarkable.makeMessage(state.range(0)));      \
    }                                                                          \
  }                                                                            \
                                                                               \
  template <class... Args>                                                     \
  static void BM_##name##_publish(benchmark::State &state, Args &&...args) {   \
    auto publisher = std::make_shared<MinimalPublisher<tmpl>>();               \
    benchmarkable_type benchmarkable(publisher.get());                         \
    for (auto _ : state) {                                                     \
      auto result = (benchmarkable.serialize(                                  \
          benchmarkable.makeMessage(state.range(0))));                         \
      benchmarkable.setSerializedResult(&result);                              \
      benchmarkable.publish();                                                 \
    }                                                                          \
  }                                                                            \
  /* CREATE_BM(BM_##name); */                                                  \
  CREATE_BM(BM_##name##_publish);

#define ADD_BM(name, benchmarkable_type)                                       \
  ADD_BM_TMPL(name, benchmarkable_type, std_msgs::msg::UInt8MultiArray)

ADD_BM(capnp, CapnpBenchmarkable);
ADD_BM(proto2, Proto2Benchmarkable);
ADD_BM(proto3, Proto3Benchmarkable);
ADD_BM(proto3_arena, Proto3ArenaBenchmarkable);
ADD_BM(upb, UpbBenchmarkable);
ADD_BM(nanopb, NanoPbBenchmarkable);
ADD_BM(flatbuf, FbsBenchmarkable);
ADD_BM_TMPL(ros2, Ros2Benchmarkable, robolog_interface::msg::Robolog);

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();

  return 0;
}
