#pragma once

#include <iostream>

#include "msgs/robolog_fbs_generated.h"
#include "src/benchmark.h"
#include "src/consts.h"

template <typename Type>
Type *GetMutablePointer(flatbuffers::FlatBufferBuilder &builder,
                        const flatbuffers::Offset<Type> &object) {
  return (reinterpret_cast<Type *>(builder.GetCurrentBufferPointer() +
                                   builder.GetSize() - object.o));
}

template <typename Type>
Type *GetPointer(flatbuffers::FlatBufferBuilder &builder,
                 flatbuffers::Offset<Type> &object) {
  return (reinterpret_cast<Type *>(builder.GetCurrentBufferPointer() +
                                   builder.GetSize() - object.o));
}

template <typename Type>
const Type *GetPointer(flatbuffers::FlatBufferBuilder &builder,
                       const flatbuffers::Offset<Type> &object) {
  return (reinterpret_cast<const Type *>(builder.GetCurrentBufferPointer() +
                                         builder.GetSize() - object.o));
}

class FbsBenchmarkable
    : public Benchmarkable<flatbuffers::Offset<robolog_fbs::MyLog>,
                           std_msgs::msg::UInt8MultiArray> {
public:
  FbsBenchmarkable(MinimalPublisher<std_msgs::msg::UInt8MultiArray> *publisher)
      : Benchmarkable(publisher), fbs_builder_(1024) {}

  const SerializeResult
  serialize(const flatbuffers::Offset<robolog_fbs::MyLog> message) {
    return {
        .data = reinterpret_cast<const std::byte *>(
            fbs_builder_.GetBufferPointer()),
        .size = fbs_builder_.GetSize(),
    };
  }

  flatbuffers::Offset<robolog_fbs::MyLog> makeMessage(const size_t num_cycles) {
    fbs_builder_.Clear();

    auto git_commit_sha = fbs_builder_.CreateString("abcdef12345");
    robolog_fbs::Robot robot = robolog_fbs::Robot_Autumn;
    uint64_t timestamp = 1234567890;
    auto metadata = robolog_fbs::CreateMetadata(fbs_builder_, robot,
                                                git_commit_sha, timestamp);

    std::vector<flatbuffers::Offset<robolog_fbs::RTCycle>> rtcycle_offsets;
    rtcycle_offsets.reserve(num_cycles);

    for (size_t i = 0; i < num_cycles; ++i) {
      flatbuffers::Offset<robolog_fbs::PhysicalState> leg_states[4];
      for (int j = 0; j < 4; ++j) {
        float position = getRandom();
        float velocity = getRandom();
        float acceleration = getRandom();
        leg_states[j] = robolog_fbs::CreatePhysicalState(
            fbs_builder_, position, velocity, acceleration);
      }
      auto leg_states_vector = fbs_builder_.CreateVector(leg_states, 4);

      float x = getRandom();
      float y = getRandom();
      float z = getRandom();
      flatbuffers::Offset<robolog_fbs::Pose3D> pose =
          robolog_fbs::CreatePose3D(fbs_builder_, x, y, z);

      auto rtcycle = robolog_fbs::CreateRTCycle(
          fbs_builder_, leg_states_vector,
          robolog_fbs::CreatePhysicalState(fbs_builder_, getRandom(),
                                           getRandom(), getRandom()),
          robolog_fbs::CreatePhysicalState(fbs_builder_, getRandom(),
                                           getRandom(), getRandom()),
          pose);

      rtcycle_offsets.emplace_back(rtcycle);
    }

    auto cycles_vector = fbs_builder_.CreateVector(rtcycle_offsets);
    auto mylog =
        robolog_fbs::CreateMyLog(fbs_builder_, metadata, cycles_vector);
    fbs_builder_.Finish(mylog);

    return mylog;
  }

  flatbuffers::FlatBufferBuilder fbs_builder_;
};
