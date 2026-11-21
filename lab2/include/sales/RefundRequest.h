#pragma once
#include <string>
#include <vector>
#include "Payment.h"
class CashRegister;
class InvalidOrder;

/// Запрос на возврат платежа.
class RefundRequest {
 public:
  RefundRequest(Payment& payment, const std::string& reason) : payment_(payment), reason_(reason) {}
  void Validate() const;
  void Resolve(CashRegister& cash);
  int RequestedAmount() const;
  const Payment& GetPayment() const { return payment_; }
  const std::string& GetReason() const { return reason_; }
  bool GetResolved() const { return resolved_; }
 private:
  Payment& payment_;
  std::string reason_;
  bool resolved_ = false;
};
