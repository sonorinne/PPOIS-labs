#include "StockAudit.h"
#include "StockRoom.h"
#include "InvalidOrder.h"

void StockAudit::Capture(const StockRoom& stock) {
  snapshot_ = stock;
  captured_ = true;
}

int StockAudit::TotalGrams() const {
  if (!captured_) throw InvalidOrder();
  int total = 0;
  for (const auto& item : snapshot_.GetItems()) total += item.GetGrams();
  return total;
}

int StockAudit::Difference(const StockRoom& current) const {
  StockAudit audit;
  audit.Capture(current);
  return TotalGrams() - audit.TotalGrams();
}
