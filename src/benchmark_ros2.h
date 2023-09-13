#pragma once

#include <iostream>

#include "msgs/ros/robolog_interface/msg/metadata.hpp"
#include "msgs/ros/robolog_interface/msg/physical_state.hpp"
#include "msgs/ros/robolog_interface/msg/pose3_d.hpp"
#include "msgs/ros/robolog_interface/msg/robolog.hpp"
#include "msgs/ros/robolog_interface/msg/robot.hpp"
#include "msgs/ros/robolog_interface/msg/rt_cycle.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/serialization.hpp"
#include "src/benchmark.h"
#include "src/consts.h"

class Ros2Benchmarkable
    : public Benchmarkable<robolog_interface::msg::Robolog> {
public:
  Ros2Benchmarkable() : Benchmarkable() {}

  const SerializeResult serialize(robolog_interface::msg::Robolog message) {
    auto msg_ptr = std::make_shared<robolog_interface::msg::Robolog>(message);
    ser.serialize_message(msg_ptr.get(), &out);

    return {
        .data = reinterpret_cast<const std::byte *>(
            out.get_rcl_serialized_message().buffer),
        .size = out.size(),
    };
  }

  robolog_interface::msg::Robolog makeMessage(const size_t num_cycles) {
    robolog_interface::msg::Robolog robolog_msg;

    // Create a Metadata message and set its fields
    robolog_interface::msg::Metadata metadata_msg;
    metadata_msg.robot =
        robolog_interface::msg::Robot::AUTUMN; // Set enum value
    metadata_msg.git_commit_sha = "abcdef12345";
    metadata_msg.timestamp = 1234567890;
    robolog_msg.metadata = metadata_msg;

    robolog_msg.cycles.reserve(num_cycles);

    for (size_t i = 0; i < num_cycles; i++) {
      robolog_interface::msg::RTCycle rtcycle_msg;
      rtcycle_msg.leg_states.reserve(4);

      for (int j = 0; j < 4; j++) {
        robolog_interface::msg::PhysicalState leg_state_msg;
        leg_state_msg.position = getRandom();
        leg_state_msg.velocity = getRandom();
        leg_state_msg.acceleration = getRandom();
        rtcycle_msg.leg_states.emplace_back(leg_state_msg);
      }

      robolog_interface::msg::PhysicalState arm_state_msg;
      arm_state_msg.position = getRandom();
      arm_state_msg.velocity = getRandom();
      arm_state_msg.acceleration = getRandom();
      rtcycle_msg.arm_state = arm_state_msg;

      robolog_interface::msg::PhysicalState elbow_state_msg;
      elbow_state_msg.position = getRandom();
      elbow_state_msg.velocity = getRandom();
      elbow_state_msg.acceleration = getRandom();
      rtcycle_msg.elbow_state = elbow_state_msg;

      robolog_interface::msg::Pose3D pose_msg;
      pose_msg.x = getRandom();
      pose_msg.y = getRandom();
      pose_msg.z = getRandom();
      rtcycle_msg.pose = pose_msg;

      robolog_msg.cycles.emplace_back(rtcycle_msg);
    }

    return robolog_msg;
  }

  rclcpp::Serialization<robolog_interface::msg::Robolog> ser;
  rclcpp::SerializedMessage out;
};
