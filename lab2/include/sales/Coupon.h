#pragma once
#include <string>
#include <vector>

class Customer;
class Order;

/// Скидочный купон.
class Coupon {
 public:
  int Discount(const Order& order) const;
  void Redeem(Order& order);
  bool Eligible(const Customer& customer) const;
  const std::string& GetCode() const { return code_; }
  int GetPercent() const { return percent_; }
  int GetMinimum() const { return minimum_; }
  bool GetUsed() const { return used_; }

 private:
  std::string code_ = "WELCOME";
  int percent_ = 10;
  int minimum_ = 500;
  bool used_ = false;
};
