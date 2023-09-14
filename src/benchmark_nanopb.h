#pragma once

#include <cstring>
#include <iostream>

#include "msgs/robolog_npb.pb.h"
#include "pb_encode.h"
#include "src/benchmark.h"
#include "src/consts.h"

class NanoPbBenchmarkable
    : public Benchmarkable<robolog_npb_Robolog,
                           std_msgs::msg::UInt8MultiArray> {
public:
  NanoPbBenchmarkable(
      MinimalPublisher<std_msgs::msg::UInt8MultiArray> *publisher)
      : Benchmarkable(publisher) {}

  const SerializeResult serialize(robolog_npb_Robolog message) {
    std::memset(buffer, 0, sizeof(buffer));

    pb_ostream_t ostream =
        pb_ostream_from_buffer(buffer, robolog_npb_Robolog_size);
    pb_encode(&ostream, robolog_npb_Robolog_fields, &message);

    return {
        .data = reinterpret_cast<const std::byte *>(buffer),
        .size = ostream.bytes_written,
    };
  }

  robolog_npb_Robolog makeMessage(const size_t num_cycles) {
    robolog_npb_Robolog robolog = robolog_npb_Robolog_init_zero;
    robolog_npb_Metadata *metadata = &robolog.metadata;

    metadata->robot = robolog_npb_Robot_Autumn;
    strncpy(metadata->git_commit_sha, "abcdef12345",
            sizeof(metadata->git_commit_sha));
    metadata->git_commit_sha[sizeof(metadata->git_commit_sha) - 1] = '\0';
    metadata->timestamp = 1234567890;

    robolog.cycles_count = num_cycles;
    for (size_t i = 0; i < num_cycles; i++) {
      robolog.cycles[i].leg_states_count = 4;

      for (int j = 0; j < 4; j++) {
        robolog.cycles[i].leg_states[j] = robolog_npb_PhysicalState_init_zero;
        robolog.cycles[i].leg_states[j].position = getRandom();
        robolog.cycles[i].leg_states[j].velocity = getRandom();
        robolog.cycles[i].leg_states[j].acceleration = getRandom();
      }

      robolog.cycles[i].arm_state.position = getRandom();
      robolog.cycles[i].arm_state.velocity = getRandom();
      robolog.cycles[i].arm_state.acceleration = getRandom();

      robolog.cycles[i].elbow_state.position = getRandom();
      robolog.cycles[i].elbow_state.velocity = getRandom();
      robolog.cycles[i].elbow_state.acceleration = getRandom();

      robolog.cycles[i].pose.x = getRandom();
      robolog.cycles[i].pose.y = getRandom();
      robolog.cycles[i].pose.z = getRandom();
    }

    return robolog;
  }

  uint8_t buffer[robolog_npb_Robolog_size];
  size_t s;
};
