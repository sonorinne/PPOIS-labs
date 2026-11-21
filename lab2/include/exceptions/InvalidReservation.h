#pragma once
#include <stdexcept>

/// Domain error: InvalidReservation.
class InvalidReservation : public std::runtime_error {
 public:
  InvalidReservation() : std::runtime_error("InvalidReservation") {}
};
