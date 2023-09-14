#pragma once

#include <iostream>

#include "msgs/robolog_pb2.pb.h"
#include "src/benchmark.h"
#include "src/consts.h"

class Proto2Benchmarkable
    : public Benchmarkable<robolog_pb2::Robolog,
                           std_msgs::msg::UInt8MultiArray> {
public:
  Proto2Benchmarkable(
      MinimalPublisher<std_msgs::msg::UInt8MultiArray> *publisher)
      : Benchmarkable(publisher) {}

  const SerializeResult serialize(robolog_pb2::Robolog message) {
    message.SerializeToString(&s);
    return {
        .data = reinterpret_cast<const std::byte *>(s.data()),
        .size = s.size(),
    };
  }

  robolog_pb2::Robolog makeMessage(const size_t num_cycles) {
    robolog_pb2::Robolog myLog;

    robolog_pb2::Metadata *metadata = myLog.mutable_metadata();
    metadata->set_robot(robolog_pb2::Robot::Autumn);
    metadata->set_git_commit_sha("abcdef12345");
    metadata->set_timestamp(1234567890);

    myLog.mutable_cycles()->Reserve(num_cycles);

    for (size_t i = 0; i < num_cycles; i++) {
      robolog_pb2::RTCycle *cycle = myLog.add_cycles();
      for (int j = 0; j < 4; j++) {
        cycle->mutable_leg_states()->Reserve(4);

        robolog_pb2::PhysicalState *legState = cycle->add_leg_states();
        legState->set_position(getRandom());
        legState->set_velocity(getRandom());
        legState->set_acceleration(getRandom());
      }
      robolog_pb2::PhysicalState *armState = cycle->mutable_arm_state();
      armState->set_position(getRandom());
      armState->set_velocity(getRandom());
      armState->set_acceleration(getRandom());

      robolog_pb2::PhysicalState *elbowState = cycle->mutable_elbow_state();
      elbowState->set_position(getRandom());
      elbowState->set_velocity(getRandom());
      elbowState->set_acceleration(getRandom());

      robolog_pb2::Pose3D *pose = cycle->mutable_pose();
      pose->set_x(getRandom());
      pose->set_y(getRandom());
      pose->set_z(getRandom());
    }

    return myLog;
  }

  std::string s;
};
