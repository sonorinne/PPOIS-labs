#pragma once
#include <stdexcept>

/// Domain error: UnavailableItem.
class UnavailableItem : public std::runtime_error {
 public:
  UnavailableItem() : std::runtime_error("UnavailableItem") {}
};
