#include "Order.h"
#include "OrderLine.h"
#include "InvalidOrder.h"

void Order::Add(const OrderLine& line) {
  if (confirmed_ || cancelled_) throw InvalidOrder();
  lines_.push_back(line);
}

int Order::Subtotal() const {
  int total = 0;
  for (const auto& line : lines_) total += line.Total();
  return total;
}

int Order::Total() const {
  return Subtotal() - discount_;
}

void Order::ApplyDiscount(int amount) {
  if (confirmed_ || cancelled_ || amount < 0 || amount > Subtotal()) throw InvalidOrder();
  discount_ = amount;
}

void Order::Confirm() {
  if (lines_.empty() || confirmed_ || cancelled_) throw InvalidOrder();
  confirmed_ = true;
}

void Order::Cancel() {
  if (cancelled_) throw InvalidOrder();
  cancelled_ = true;
}
