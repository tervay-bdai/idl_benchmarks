#pragma once

#include <iostream>

#include "msgs/robolog_upb.upb.h"
#include "src/benchmark.h"
#include "src/consts.h"

#include "upb/reflection/def.h"
#include "upb/reflection/def.hpp"

class UpbBenchmarkable : public Benchmarkable {
public:
  UpbBenchmarkable() : Benchmarkable() {}

  const SerializeResult serialize() {
    const auto a = arena_.ptr();

    robolog_upb_Robolog *log = robolog_upb_Robolog_new(a);

    robolog_upb_Metadata *metadata = robolog_upb_Metadata_new(a);
    robolog_upb_Metadata_set_robot(metadata, robolog_upb_Autumn);
    robolog_upb_Metadata_set_git_commit_sha(
        metadata, upb_StringView_FromString("abcdef12345"));
    robolog_upb_Metadata_set_timestamp(metadata, 1234567890);
    robolog_upb_Robolog_set_metadata(log, metadata);

    robolog_upb_RTCycle *cycle = robolog_upb_Robolog_add_cycles(log, a);
    for (int i = 0; i < 4; i++) {
      robolog_upb_PhysicalState *legState =
          robolog_upb_RTCycle_add_leg_states(cycle, a);

      robolog_upb_PhysicalState_set_position(legState, 1.0f * i);
      robolog_upb_PhysicalState_set_velocity(legState, 2.0f * i);
      robolog_upb_PhysicalState_set_acceleration(legState, 3.0f * i);
    }

    robolog_upb_PhysicalState *armState =
        robolog_upb_RTCycle_mutable_arm_state(cycle, a);
    robolog_upb_PhysicalState_set_position(armState, 10.0f);
    robolog_upb_PhysicalState_set_velocity(armState, 20.0f);
    robolog_upb_PhysicalState_set_acceleration(armState, 30.0f);

    robolog_upb_PhysicalState *elbowState =
        robolog_upb_RTCycle_mutable_elbow_state(cycle, a);
    robolog_upb_PhysicalState_set_position(elbowState, 100.0f);
    robolog_upb_PhysicalState_set_velocity(elbowState, 200.0f);
    robolog_upb_PhysicalState_set_acceleration(elbowState, 300.0f);

    robolog_upb_Pose3D *pose = robolog_upb_RTCycle_mutable_pose(cycle, a);
    robolog_upb_Pose3D_set_x(pose, 1.0f);
    robolog_upb_Pose3D_set_y(pose, 2.0f);
    robolog_upb_Pose3D_set_z(pose, 3.0f);

    s_.data = robolog_upb_Robolog_serialize(log, a, &s_.size);
    return {
        .data = reinterpret_cast<const std::byte *>(s_.data),
        .size = s_.size,
    };
  }

  upb::DefPool defpool_;
  upb::Arena arena_;
  upb_StringView s_;
};
