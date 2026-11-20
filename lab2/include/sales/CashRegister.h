#pragma once
#include <string>
#include <vector>

class Payment;

/// Касса.
class CashRegister {
 public:
  void Accept(Payment& payment);
  void Refund(Payment& payment);
  int Close();
  int GetBalance() const { return balance_; }
  int GetRevenue() const { return revenue_; }
  int GetRefunds() const { return refunds_; }
  bool GetOpen() const { return open_; }

 private:
  int balance_ = 0;
  int revenue_ = 0;
  int refunds_ = 0;
  bool open_ = true;
};
