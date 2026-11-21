#pragma once
#include <stdexcept>

/// Domain error: InvalidAmount.
class InvalidAmount : public std::runtime_error {
 public:
  InvalidAmount() : std::runtime_error("InvalidAmount") {}
};
