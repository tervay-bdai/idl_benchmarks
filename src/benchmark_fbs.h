#pragma once

#include <iostream>

#include "msgs/robolog_fbs_generated.h"
#include "src/benchmark.h"
#include "src/consts.h"

class FbsBenchmarkable : public Benchmarkable {
public:
  FbsBenchmarkable() : Benchmarkable(), fbs_builder_(1024) {}

  void serialize() {
    // Clear the existing data in the builder
    fbs_builder_.Clear();

    // Create a Metadata object
    auto git_commit_sha = fbs_builder_.CreateString("abcdef12345");
    robolog_fbs::Robot robot = robolog_fbs::Robot_Autumn;
    uint64_t timestamp = 1234567890;
    auto metadata = robolog_fbs::CreateMetadata(fbs_builder_, robot,
                                                git_commit_sha, timestamp);

    // Create PhysicalState objects
    float position = 1.0f;
    float velocity = 2.0f;
    float acceleration = 3.0f;
    flatbuffers::Offset<robolog_fbs::PhysicalState> leg_states[4];

    leg_states[0] = robolog_fbs::CreatePhysicalState(fbs_builder_, position,
                                                     velocity, acceleration);
    leg_states[1] = robolog_fbs::CreatePhysicalState(
        fbs_builder_, position * 2, velocity * 2, acceleration * 2);
    leg_states[2] = robolog_fbs::CreatePhysicalState(
        fbs_builder_, position * 3, velocity * 3, acceleration * 3);
    leg_states[3] = robolog_fbs::CreatePhysicalState(
        fbs_builder_, position * 4, velocity * 4, acceleration * 4);

    auto leg_states_vector = fbs_builder_.CreateVector(leg_states, 4);

    // Create Pose3D object
    float x = 1.0f;
    float y = 2.0f;
    float z = 3.0f;
    auto pose = robolog_fbs::CreatePose3D(fbs_builder_, x, y, z);

    // Create RTCycle object
    auto rtcycle = robolog_fbs::CreateRTCycle(
        fbs_builder_, leg_states_vector,
        robolog_fbs::CreatePhysicalState(fbs_builder_, 10.0f, 20.0f, 30.0f),
        robolog_fbs::CreatePhysicalState(fbs_builder_, 100.0f, 200.0f, 300.0f),
        pose);

    // Create MyLog object
    flatbuffers::Offset<robolog_fbs::RTCycle> cycles[] = {rtcycle};
    auto cycles_vector = fbs_builder_.CreateVector(cycles, 1);
    auto mylog =
        robolog_fbs::CreateMyLog(fbs_builder_, metadata, cycles_vector);

    // Finish building the buffer
    fbs_builder_.Finish(mylog);
  }

  flatbuffers::FlatBufferBuilder fbs_builder_;
};
