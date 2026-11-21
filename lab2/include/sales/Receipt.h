#pragma once
#include <string>
#include <vector>
#include "Order.h"
#include "Payment.h"
class InvalidAmount;
class InvalidOrder;

/// Чек для оплаченного заказа.
class Receipt {
 public:
  Receipt() = default;
  Receipt(const Order& order, const Payment& payment) : order_(order), payment_(payment) {}
  void Validate() const;
  int Total() const;
  std::string Text() const;
  const Order& GetOrder() const { return order_; }
  const Payment& GetPayment() const { return payment_; }
  const std::string& GetShop() const { return shop_; }
 private:
  Order order_;
  Payment payment_;
  std::string shop_ = "Pizzeria";
};
