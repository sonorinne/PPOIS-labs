#pragma once
#include <stdexcept>

/// Domain error: InvalidAddress.
class InvalidAddress : public std::runtime_error {
 public:
  InvalidAddress() : std::runtime_error("InvalidAddress") {}
};
