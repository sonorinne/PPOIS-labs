#pragma once
#include <stdexcept>

/// Domain error: UnavailableOven.
class UnavailableOven : public std::runtime_error {
 public:
  UnavailableOven() : std::runtime_error("UnavailableOven") {}
};
