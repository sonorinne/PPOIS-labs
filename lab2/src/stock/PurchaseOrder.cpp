#include "PurchaseOrder.h"
#include "Supplier.h"
#include "PurchaseLine.h"
#include "InvalidOrder.h"
#include "InsufficientPayment.h"

void PurchaseOrder::Add(const PurchaseLine& line) {
  if (closed_ || !supplier_.GetActive()) throw InvalidOrder();
  lines_.push_back(line);
}

int PurchaseOrder::Total() const {
  int total = 0;
  for (const auto& line : lines_) total += line.Total();
  return total;
}

void PurchaseOrder::Close(int payment) {
  if (closed_ || lines_.empty()) throw InvalidOrder();
  if (payment < Total()) throw InsufficientPayment();
  paid_ = Total();
  closed_ = true;
}
