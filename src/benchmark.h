#pragma once

#include <chrono>

struct SerializeResult {
  const std::byte *data;
  const size_t size;
};

template <typename T> class Benchmarkable {
public:
  Benchmarkable() {}
  virtual ~Benchmarkable() {}
  virtual const SerializeResult serialize(T message) = 0;
  virtual T makeMessage() = 0;
};
