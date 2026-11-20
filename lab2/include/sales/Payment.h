#pragma once
#include <string>
#include <vector>

class Order;

/// Платёж за заказ.
class Payment {
 public:
  void Capture(const Order& order, int tendered);
  int Refund();
  int Net() const;
  void Register();
  int GetAmount() const { return amount_; }
  int GetChange() const { return change_; }
  bool GetCaptured() const { return captured_; }
  bool GetRefunded() const { return refunded_; }
  bool GetRegistered() const { return registered_; }

 private:
  int amount_ = 0;
  int change_ = 0;
  bool captured_ = false;
  bool refunded_ = false;
  bool registered_ = false;
};
