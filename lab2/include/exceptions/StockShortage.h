#pragma once
#include <stdexcept>

/// Domain error: StockShortage.
class StockShortage : public std::runtime_error {
 public:
  StockShortage() : std::runtime_error("StockShortage") {}
};
