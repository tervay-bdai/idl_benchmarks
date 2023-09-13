#define TEST_OVERRIDE_RANDOM

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "src/benchmark_nanopb.h"
#include "src/benchmark_proto2.h"
#include "src/benchmark_proto3.h"
#include "src/benchmark_upb.h"

using ::testing::Not;

MATCHER_P(EquivalentSerializeResult, expected, "") {
  if (arg.size != expected.size) {
    *result_listener << "Expected size: " << expected.size
                     << ", actual size: " << arg.size;
    return false;
  }

  for (size_t i = 0; i < arg.size; ++i) {
    if (arg.data[i] != expected.data[i]) {
      *result_listener << "Mismatch at position " << i;
      return false;
    }
  }

  return true;
}

TEST(CustomMatcherTest, SerializeResultEquality) {
  SerializeResult expected_result = {
      reinterpret_cast<const std::byte *>("Hello"), 5};
  SerializeResult actual_result = {reinterpret_cast<const std::byte *>("Hello"),
                                   5};

  EXPECT_THAT(actual_result, EquivalentSerializeResult(expected_result));
}

TEST(CustomMatcherTest, SerializeResultInequalityDifferentDataAndLength) {
  SerializeResult expected_result = {
      reinterpret_cast<const std::byte *>("Hello"), 5};
  SerializeResult actual_result = {
      reinterpret_cast<const std::byte *>("Hello "), 6};

  EXPECT_THAT(actual_result, Not(EquivalentSerializeResult(expected_result)));
}

TEST(CustomMatcherTest, SerializeResultInequalityDifferentDataSameLength) {
  SerializeResult expected_result = {
      reinterpret_cast<const std::byte *>("Hello"), 5};
  SerializeResult actual_result = {reinterpret_cast<const std::byte *>("World"),
                                   5};

  EXPECT_THAT(actual_result, Not(EquivalentSerializeResult(expected_result)));
}

TEST(CustomMatcherTest, SerializeResultInequalitySameDataDifferentLength) {
  SerializeResult expected_result = {
      reinterpret_cast<const std::byte *>("Hello"), 5};
  SerializeResult actual_result = {reinterpret_cast<const std::byte *>("Hello"),
                                   4};

  EXPECT_THAT(actual_result, Not(EquivalentSerializeResult(expected_result)));
}

class Pb2Test : public testing::TestWithParam<size_t> {};

TEST_P(Pb2Test, EqualsUpbSerialization) {
  Proto2Benchmarkable pb2;
  UpbBenchmarkable upb;

  EXPECT_THAT(pb2.serialize(pb2.makeMessage(1)),
              EquivalentSerializeResult(upb.serialize(upb.makeMessage(1))));
}

TEST_P(Pb2Test, EqualsNpbSerialization) {
  Proto2Benchmarkable pb2;
  NanoPbBenchmarkable npb;

  EXPECT_THAT(pb2.serialize(pb2.makeMessage(1)),
              EquivalentSerializeResult(npb.serialize(npb.makeMessage(1))));
}

INSTANTIATE_TEST_SUITE_P(RTCycleSizes, Pb2Test, testing::Values(1, 5, 10));
