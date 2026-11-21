#pragma once
#include <string>
#include <vector>
#include "StockRoom.h"
class InvalidOrder;

/// Инвентаризация остатков.
class StockAudit {
 public:
  void Capture(const StockRoom& stock);
  int TotalGrams() const;
  int Difference(const StockRoom& current) const;
  const StockRoom& GetSnapshot() const { return snapshot_; }
  bool GetCaptured() const { return captured_; }
 private:
  StockRoom snapshot_;
  bool captured_ = false;
};
