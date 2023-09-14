#pragma once

#include <cstring>
#include <iostream>
#include <memory>

#include "capnp/compat/json.h"
#include "capnp/message.h"
#include "capnp/serialize-packed.h"
#include "msgs/robolog_cnp.capnp.h"
#include "src/benchmark.h"
#include "src/consts.h"

class CapnpBenchmarkable
    : public Benchmarkable<SerializeResult, std_msgs::msg::UInt8MultiArray> {
public:
  CapnpBenchmarkable(
      MinimalPublisher<std_msgs::msg::UInt8MultiArray> *publisher)
      : Benchmarkable(publisher) {}

  const SerializeResult serialize(const SerializeResult ser) { return ser; }

  SerializeResult makeMessage(const size_t num_cycles) {
    capnp::MallocMessageBuilder message;

    robolog_cnp::Robolog::Builder robolog_builder =
        message.initRoot<robolog_cnp::Robolog>();
    robolog_cnp::Metadata::Builder metadata_builder =
        robolog_builder.initMetadata();

    metadata_builder.setGitCommitSha("abcdef12345");
    metadata_builder.setRobot(robolog_cnp::Robot::AUTUMN);
    metadata_builder.setTimestamp(1234567890);

    auto rt_cycles = robolog_builder.initCycles(num_cycles);
    for (size_t i = 0; i < num_cycles; i++) {
      rt_cycles[i].getArmState().setPosition(getRandom());
      rt_cycles[i].getArmState().setVelocity(getRandom());
      rt_cycles[i].getArmState().setAcceleration(getRandom());

      rt_cycles[i].getElbowState().setPosition(getRandom());
      rt_cycles[i].getElbowState().setVelocity(getRandom());
      rt_cycles[i].getElbowState().setAcceleration(getRandom());

      rt_cycles[i].getPose().setX(getRandom());
      rt_cycles[i].getPose().setY(getRandom());
      rt_cycles[i].getPose().setZ(getRandom());

      auto leg_states = rt_cycles[i].initLegStates(4);
      for (int j = 0; j < 4; j++) {
        leg_states[j].setPosition(getRandom());
        leg_states[j].setVelocity(getRandom());
        leg_states[j].setAcceleration(getRandom());
      }
    }

    arr = capnp::messageToFlatArray(message);
    auto c = arr.asBytes();

    return {
        .data = reinterpret_cast<std::byte *>(c.begin()),
        .size = c.size(),
    };
  }

  kj::Array<capnp::word> arr;
};
