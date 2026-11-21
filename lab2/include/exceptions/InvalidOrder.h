#pragma once
#include <stdexcept>

/// Domain error: InvalidOrder.
class InvalidOrder : public std::runtime_error {
 public:
  InvalidOrder() : std::runtime_error("InvalidOrder") {}
};
