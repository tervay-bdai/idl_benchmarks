#include "gtest/gtest.h"

#include "src/benchmark_nanopb.h"
#include "src/benchmark_proto2.h"
#include "src/benchmark_proto3.h"
#include "src/benchmark_upb.h"

TEST(Pb2Test, EqualsUpb) {
  Proto2Benchmarkable pb2;
  UpbBenchmarkable upb;

  auto pb2_ser = pb2.serialize(pb2.makeMessage());
  auto upb_ser = upb.serialize(upb.makeMessage());

  EXPECT_EQ(pb2_ser.size, upb_ser.size);
}

TEST(Pb2Test, EqualsNpb) {
  Proto2Benchmarkable pb2;
  NanoPbBenchmarkable npb;

  auto pb2_ser = pb2.serialize(pb2.makeMessage());
  auto npb_ser = npb.serialize(npb.makeMessage());

  EXPECT_EQ(pb2_ser.size, npb_ser.size);
}