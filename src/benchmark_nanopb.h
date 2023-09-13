#pragma once

#include <cstring>
#include <iostream>

#include "msgs/robolog_npb.pb.h"
#include "pb_encode.h"
#include "src/benchmark.h"
#include "src/consts.h"

class NanoPbBenchmarkable : public Benchmarkable<robolog_npb_Robolog> {
public:
  NanoPbBenchmarkable() : Benchmarkable() {}

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

  robolog_npb_Robolog makeMessage() {
    robolog_npb_Robolog robolog = robolog_npb_Robolog_init_zero;
    robolog_npb_Metadata *metadata = &robolog.metadata;

    // Populate the fields
    metadata->robot = robolog_npb_Robot_Autumn;
    strncpy(metadata->git_commit_sha, "abcdef12345",
            sizeof(metadata->git_commit_sha));
    metadata->git_commit_sha[sizeof(metadata->git_commit_sha) - 1] = '\0';
    metadata->timestamp = 1234567890;

    for (int i = 0; i < 4; i++) {
      robolog.cycles[0].leg_states[i] = robolog_npb_PhysicalState_init_zero;
      robolog.cycles[0].leg_states[i].position = 1.0f * i;
      robolog.cycles[0].leg_states[i].velocity = 2.0f * i;
      robolog.cycles[0].leg_states[i].acceleration = 3.0f * i;
    }

    robolog.cycles_count = 1;
    robolog.cycles[0].leg_states_count = 4;

    robolog.cycles[0].arm_state.position = 10.0f;
    robolog.cycles[0].arm_state.velocity = 20.0f;
    robolog.cycles[0].arm_state.acceleration = 30.0f;

    robolog.cycles[0].elbow_state.position = 100.0f;
    robolog.cycles[0].elbow_state.velocity = 200.0f;
    robolog.cycles[0].elbow_state.acceleration = 300.0f;

    robolog.cycles[0].pose.x = 1.0f;
    robolog.cycles[0].pose.y = 2.0f;
    robolog.cycles[0].pose.z = 3.0f;

    return robolog;
  }

  uint8_t buffer[robolog_npb_Robolog_size];
  size_t s;
};
