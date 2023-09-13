#pragma once

#include <iostream>

#include "msgs/robolog_pb3.pb.h"
#include "src/benchmark.h"
#include "src/consts.h"

class Proto3Benchmarkable : public Benchmarkable<robolog_pb3::Robolog> {
public:
  Proto3Benchmarkable() : Benchmarkable() {}

  const SerializeResult serialize(robolog_pb3::Robolog message) {
    message.SerializeToString(&s);
    return {
        .data = reinterpret_cast<const std::byte *>(s.data()),
        .size = s.size(),
    };
  }

  robolog_pb3::Robolog makeMessage(const size_t num_cycles) {
    robolog_pb3::Robolog myLog;

    robolog_pb3::Metadata *metadata = myLog.mutable_metadata();
    metadata->set_robot(robolog_pb3::Robot::Autumn);
    metadata->set_git_commit_sha("abcdef12345");
    metadata->set_timestamp(1234567890);

    // Populate RTCycle
    robolog_pb3::RTCycle *cycle = myLog.add_cycles();
    for (int i = 0; i < 4; i++) {
      robolog_pb3::PhysicalState *legState = cycle->add_leg_states();
      legState->set_position(1.0f * i);
      legState->set_velocity(2.0f * i);
      legState->set_acceleration(3.0f * i);
    }
    robolog_pb3::PhysicalState *armState = cycle->mutable_arm_state();
    armState->set_position(10.0f);
    armState->set_velocity(20.0f);
    armState->set_acceleration(30.0f);

    robolog_pb3::PhysicalState *elbowState = cycle->mutable_elbow_state();
    elbowState->set_position(100.0f);
    elbowState->set_velocity(200.0f);
    elbowState->set_acceleration(300.0f);

    robolog_pb3::Pose3D *pose = cycle->mutable_pose();
    pose->set_x(1.0f);
    pose->set_y(2.0f);
    pose->set_z(3.0f);

    return myLog;
  }

  std::string s;
};
