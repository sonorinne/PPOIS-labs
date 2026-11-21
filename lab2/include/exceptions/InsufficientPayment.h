#pragma once
#include <stdexcept>

/// Domain error: InsufficientPayment.
class InsufficientPayment : public std::runtime_error {
 public:
  InsufficientPayment() : std::runtime_error("InsufficientPayment") {}
};
