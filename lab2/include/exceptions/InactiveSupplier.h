#pragma once
#include <stdexcept>

/// Domain error: InactiveSupplier.
class InactiveSupplier : public std::runtime_error {
 public:
  InactiveSupplier() : std::runtime_error("InactiveSupplier") {}
};
