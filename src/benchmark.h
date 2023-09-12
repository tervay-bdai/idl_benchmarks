#pragma once

#include <chrono>

class Benchmarkable {
public:
  Benchmarkable() {}
  virtual ~Benchmarkable() {}
  virtual void serialize() = 0;
};
