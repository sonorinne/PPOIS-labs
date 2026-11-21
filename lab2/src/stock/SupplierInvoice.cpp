#include "SupplierInvoice.h"
#include "PurchaseOrder.h"
#include "InsufficientPayment.h"
#include "InvalidOrder.h"

void SupplierInvoice::Issue(const PurchaseOrder& purchase) {
  if (settled_ || !purchase.GetClosed()) throw InvalidOrder();
  purchase_ = purchase;
}

int SupplierInvoice::Outstanding() const {
  if (!purchase_.GetClosed()) throw InvalidOrder();
  return purchase_.Total() - paid_;
}

void SupplierInvoice::Settle(int amount) {
  if (settled_) throw InvalidOrder();
  if (amount < Outstanding()) throw InsufficientPayment();
  paid_ = purchase_.Total();
  settled_ = true;
}
