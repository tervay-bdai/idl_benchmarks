#pragma once

#include <chrono>

struct SerializeResult {
  const std::byte *data;
  const size_t size;
};

class Benchmarkable {
public:
  Benchmarkable() {}
  virtual ~Benchmarkable() {}
  virtual const SerializeResult serialize() = 0;
};
