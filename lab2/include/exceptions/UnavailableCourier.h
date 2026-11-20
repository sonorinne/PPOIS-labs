#pragma once
#include <stdexcept>

/// Domain error: UnavailableCourier.
class UnavailableCourier : public std::runtime_error {
 public:
  UnavailableCourier() : std::runtime_error("UnavailableCourier") {}
};
