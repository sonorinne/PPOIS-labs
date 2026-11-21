#pragma once
#include <string>
#include <vector>
#include "Order.h"
#include "Payment.h"
class InvalidOrder;

/// Сводка оплаченных продаж.
class SalesReport {
 public:
  void Record(const Order& order, const Payment& payment);
  int Revenue() const;
  int AverageCheck() const;
  const std::vector<Order>& GetOrders() const { return orders_; }
  const std::vector<Payment>& GetPayments() const { return payments_; }
 private:
  std::vector<Order> orders_;
  std::vector<Payment> payments_;
};
