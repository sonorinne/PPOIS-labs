#pragma once
#include <stdexcept>

/// Domain error: InvalidQuantity.
class InvalidQuantity : public std::runtime_error {
 public:
  InvalidQuantity() : std::runtime_error("InvalidQuantity") {}
};
