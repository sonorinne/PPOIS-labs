#include "RefundRequest.h"
#include "CashRegister.h"
#include "Payment.h"
#include "InvalidOrder.h"

void RefundRequest::Validate() const {
  if (resolved_ || reason_.empty() || !payment_.GetCaptured()) throw InvalidOrder();
}

void RefundRequest::Resolve(CashRegister& cash) {
  Validate();
  cash.Refund(payment_);
  resolved_ = true;
}

int RefundRequest::RequestedAmount() const {
  Validate();
  return payment_.GetAmount();
}
