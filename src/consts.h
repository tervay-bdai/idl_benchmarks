#pragma once

#include <random>
#include <string>
#include <string_view>

inline constexpr std::string_view PERSON_NAME = "Alice";
inline constexpr std::string_view PERSON_EMAIL = "alice@example.com";
inline constexpr std::string_view PERSON_PHONE_NUMBER = "555-123-1234";
inline constexpr int PERSON_ID = 1;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

float getRandom() {
#ifdef TEST_OVERRIDE_RANDOM
  return 4.0f; // guaranteed to be random
#else
  return distribution(gen);
#endif
}
