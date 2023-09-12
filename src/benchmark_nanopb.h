#pragma once

#include <iostream>

#include "msgs/robolog_npb.pb.h"
#include "pb_encode.h"
#include "src/benchmark.h"
#include "src/consts.h"

bool encode_string(pb_ostream_t *stream, const pb_field_t *field,
                   void *const *arg) {
  const char *str = (const char *)(*arg);

  if (!pb_encode_tag_for_field(stream, field))
    return false;

  return pb_encode_string(stream, (uint8_t *)str, strlen(str));
}

class NanoPbBenchmarkable : public Benchmarkable {
public:
  NanoPbBenchmarkable() : Benchmarkable() {}

  void serialize() {
    robolog_npb_Robolog robolog = robolog_npb_Robolog_init_zero;

    robolog.metadata.robot = robolog_npb_Robot_Autumn;
    strcpy(robolog.metadata.git_commit_sha, "abcdef12345");
    robolog.metadata.timestamp = 1234567890;

    robolog_npb_Metadata *metadata = &robolog.metadata;
    robolog_npb_RTCycle *rtcycle = robolog.cycles;
    robolog_npb_PhysicalState *leg_states = rtcycle->leg_states;
    robolog_npb_PhysicalState *arm_state = &rtcycle->arm_state;
    robolog_npb_PhysicalState *elbow_state = &rtcycle->elbow_state;
    robolog_npb_Pose3D *pose = &rtcycle->pose;

    // Populate the fields
    metadata->robot = robolog_npb_Robot_Autumn;
    strncpy(metadata->git_commit_sha, "abcdef12345",
            sizeof(metadata->git_commit_sha));
    metadata->git_commit_sha[sizeof(metadata->git_commit_sha) - 1] =
        '\0'; // Ensure null-termination
    metadata->timestamp = 1234567890;

    for (int i = 0; i < 4; i++) {
      leg_states[i].position = 1.0f * i;
      leg_states[i].velocity = 2.0f * i;
      leg_states[i].acceleration = 3.0f * i;
    }

    arm_state->position = 10.0f;
    arm_state->velocity = 20.0f;
    arm_state->acceleration = 30.0f;

    elbow_state->position = 100.0f;
    elbow_state->velocity = 200.0f;
    elbow_state->acceleration = 300.0f;

    pose->x = 1.0f;
    pose->y = 2.0f;
    pose->z = 3.0f;

    uint8_t buffer[robolog_npb_Robolog_size];
    pb_ostream_t ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    pb_encode(&ostream, robolog_npb_Robolog_fields, &robolog);
  }
};
