#include "Payment.h"
#include "Order.h"
#include "InvalidOrder.h"
#include "InsufficientPayment.h"

void Payment::Capture(const Order& order, int tendered) {
  if (captured_ || order.GetCancelled() || order.GetLines().empty()) throw InvalidOrder();
  if (tendered < order.Total()) throw InsufficientPayment();
  amount_ = order.Total();
  change_ = tendered - amount_;
  captured_ = true;
}

int Payment::Refund() {
  if (!captured_ || refunded_) throw InvalidOrder();
  refunded_ = true;
  return amount_;
}

int Payment::Net() const {
  return refunded_ ? 0 : amount_;
}

void Payment::Register() {
  if (!captured_ || refunded_ || registered_) throw InvalidOrder();
  registered_ = true;
}
