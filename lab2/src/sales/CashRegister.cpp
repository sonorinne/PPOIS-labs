#include "CashRegister.h"
#include "Payment.h"
#include "InvalidOrder.h"
#include "InsufficientPayment.h"

void CashRegister::Accept(Payment& payment) {
  if (!open_) throw InvalidOrder();
  payment.Register();
  balance_ += payment.Net();
  revenue_ += payment.Net();
}

void CashRegister::Refund(Payment& payment) {
  if (!open_ || !payment.GetCaptured() || payment.GetRefunded()) throw InvalidOrder();
  if (payment.GetAmount() > balance_) throw InsufficientPayment();
  int amount = payment.Refund();
  balance_ -= amount;
  refunds_ += amount;
}

int CashRegister::Close() {
  if (!open_) throw InvalidOrder();
  open_ = false;
  return balance_;
}
