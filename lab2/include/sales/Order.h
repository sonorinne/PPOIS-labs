#pragma once
#include <string>
#include <vector>
#include "OrderLine.h"


/// Заказ покупателя.
class Order {
 public:
  void Add(const OrderLine& line);
  int Subtotal() const;
  int Total() const;
  void ApplyDiscount(int amount);
  void Confirm();
  void Cancel();
  const std::vector<OrderLine>& GetLines() const { return lines_; }
  int GetDiscount() const { return discount_; }
  bool GetConfirmed() const { return confirmed_; }
  bool GetCancelled() const { return cancelled_; }

 private:
  std::vector<OrderLine> lines_;
  int discount_ = 0;
  bool confirmed_ = false;
  bool cancelled_ = false;
};
