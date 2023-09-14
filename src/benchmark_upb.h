#pragma once

#include <iostream>

#include "msgs/robolog_upb.upb.h"
#include "src/benchmark.h"
#include "src/consts.h"

#include "upb/reflection/def.h"
#include "upb/reflection/def.hpp"

class UpbBenchmarkable : public Benchmarkable<robolog_upb_Robolog *,
                                              std_msgs::msg::UInt8MultiArray> {
public:
  UpbBenchmarkable(MinimalPublisher<std_msgs::msg::UInt8MultiArray> *publisher)
      : Benchmarkable(publisher) {}

  const SerializeResult serialize(robolog_upb_Robolog *message) {
    s_.data = robolog_upb_Robolog_serialize(message, arena_.ptr(), &s_.size);
    return {
        .data = reinterpret_cast<const std::byte *>(s_.data),
        .size = s_.size,
    };
  }

  robolog_upb_Robolog *makeMessage(const size_t num_cycles) {
    const auto a = arena_.ptr();

    robolog_upb_Robolog *log = robolog_upb_Robolog_new(a);

    robolog_upb_Metadata *metadata = robolog_upb_Metadata_new(a);
    robolog_upb_Metadata_set_robot(metadata, robolog_upb_Autumn);
    robolog_upb_Metadata_set_git_commit_sha(
        metadata, upb_StringView_FromString("abcdef12345"));
    robolog_upb_Metadata_set_timestamp(metadata, 1234567890);
    robolog_upb_Robolog_set_metadata(log, metadata);

    for (size_t i = 0; i < num_cycles; i++) {
      robolog_upb_RTCycle *cycle = robolog_upb_Robolog_add_cycles(log, a);

      for (int j = 0; j < 4; j++) {
        robolog_upb_PhysicalState *legState =
            robolog_upb_RTCycle_add_leg_states(cycle, a);

        robolog_upb_PhysicalState_set_position(legState, getRandom());
        robolog_upb_PhysicalState_set_velocity(legState, getRandom());
        robolog_upb_PhysicalState_set_acceleration(legState, getRandom());
      }

      robolog_upb_PhysicalState *armState =
          robolog_upb_RTCycle_mutable_arm_state(cycle, a);
      robolog_upb_PhysicalState_set_position(armState, getRandom());
      robolog_upb_PhysicalState_set_velocity(armState, getRandom());
      robolog_upb_PhysicalState_set_acceleration(armState, getRandom());

      robolog_upb_PhysicalState *elbowState =
          robolog_upb_RTCycle_mutable_elbow_state(cycle, a);
      robolog_upb_PhysicalState_set_position(elbowState, getRandom());
      robolog_upb_PhysicalState_set_velocity(elbowState, getRandom());
      robolog_upb_PhysicalState_set_acceleration(elbowState, getRandom());

      robolog_upb_Pose3D *pose = robolog_upb_RTCycle_mutable_pose(cycle, a);
      robolog_upb_Pose3D_set_x(pose, getRandom());
      robolog_upb_Pose3D_set_y(pose, getRandom());
      robolog_upb_Pose3D_set_z(pose, getRandom());
    }

    return log;
  }

  upb::DefPool defpool_;
  upb::Arena arena_;
  upb_StringView s_;
};
