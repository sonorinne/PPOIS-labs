#include "SalesReport.h"
#include "Order.h"
#include "Payment.h"
#include "InvalidOrder.h"

void SalesReport::Record(const Order& order, const Payment& payment) {
  if (!payment.GetCaptured() || payment.GetRefunded() || payment.GetAmount() != order.Total()) throw InvalidOrder();
  orders_.push_back(order);
  payments_.push_back(payment);
}

int SalesReport::Revenue() const {
  int total = 0;
  for (const auto& payment : payments_) total += payment.Net();
  return total;
}

int SalesReport::AverageCheck() const {
  if (orders_.empty()) return 0;
  return Revenue() / static_cast<int>(orders_.size());
}
