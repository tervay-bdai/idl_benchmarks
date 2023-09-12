#pragma once

#include <iostream>

#include "msgs/address_book_nanopb_cc_pb/msgs/address_book_3.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "src/benchmark.h"
#include "src/consts.h"

template <typename T> struct array_handle {
  T *ptr;
  size_t len;
};

bool write_string(pb_ostream_t *stream, const pb_field_t *field,
                  void *const *arg) {
  auto argval = *arg;
  auto handle = *reinterpret_cast<array_handle<const uint8_t> *>(argval);

  if (!pb_encode_tag_for_field(stream, field))
    return false;

  return pb_encode_string(stream, handle.ptr, handle.len);
}

//! nanopb callback for writing an array
namespace helpers {
template <typename T, const pb_field_t *fields>
bool write_arrayz(pb_ostream_t *stream, const pb_field_t *field,
                  void *const *arg) {
  auto argval = *arg;
  auto handle = *reinterpret_cast<array_handle<T> *>(argval);

  for (size_t i = 0; i < handle.len; i++) {
    if (!pb_encode_tag_for_field(stream, field))
      return false;
    T *curr = handle.ptr + i;
    if (!pb_encode_submessage(stream, fields, curr))
      return false;
  }
  return true;
}
} // namespace helpers

static bool read_string(pb_istream_t *stream, const pb_field_t *field,
                        void **arg) {
  uint8_t buf[16] = {0};
  size_t len = stream->bytes_left;

  if (len > sizeof(buf) - 1 || !pb_read(stream, buf, len))
    return false;

  return true;
}

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
    uint8_t buffer[512];
    size_t message_length;

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    // pb3::AddressBook address_book;
    pb3_AddressBook address_book = pb3_AddressBook_init_zero;

    // auto person = address_book.add_people();
    pb3_Person person = pb3_Person_init_zero;

    array_handle<const char> email_handle = {PERSON_EMAIL.data(),
                                             PERSON_EMAIL.size()};
    person.email.arg = &email_handle;
    person.email.funcs.encode = encode_string;

    array_handle<const char> name_handle = {PERSON_NAME.data(),
                                            PERSON_NAME.size()};
    person.name.arg = &name_handle;
    person.name.funcs.encode = encode_string;

    pb_encode(&stream, pb3_Person_fields, &person);
    message_length = stream.bytes_written;
  }
};
