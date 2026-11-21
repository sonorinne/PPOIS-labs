#pragma once
#include <string>
#include <vector>
#include "Supplier.h"
#include "PurchaseLine.h"


/// Документ закупки.
class PurchaseOrder {
 public:
  void Add(const PurchaseLine& line);
  int Total() const;
  void Close(int payment);
  const Supplier& GetSupplier() const { return supplier_; }
  const std::vector<PurchaseLine>& GetLines() const { return lines_; }
  bool GetClosed() const { return closed_; }
  int GetPaid() const { return paid_; }

 private:
  Supplier supplier_;
  std::vector<PurchaseLine> lines_;
  bool closed_ = false;
  int paid_ = 0;
};
