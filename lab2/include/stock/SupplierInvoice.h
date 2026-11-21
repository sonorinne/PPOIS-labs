#pragma once
#include <string>
#include <vector>
#include "PurchaseOrder.h"
class InsufficientPayment;
class InvalidOrder;

/// Счёт по закрытой закупке.
class SupplierInvoice {
 public:
  void Issue(const PurchaseOrder& purchase);
  int Outstanding() const;
  void Settle(int amount);
  const PurchaseOrder& GetPurchase() const { return purchase_; }
  int GetPaid() const { return paid_; }
  bool GetSettled() const { return settled_; }
 private:
  PurchaseOrder purchase_;
  int paid_ = 0;
  bool settled_ = false;
};
