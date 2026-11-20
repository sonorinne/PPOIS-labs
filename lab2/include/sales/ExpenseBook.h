#pragma once
#include <string>
#include <vector>

class PurchaseOrder;
class WorkShift;
class InvalidOrder;
class WasteRecord;

/// Учёт закупок, зарплаты и списаний.
class ExpenseBook {
 public:
  void RecordPurchase(const PurchaseOrder& purchase);
  void RecordShift(const WorkShift& shift);
  void RecordWaste(const WasteRecord& record);
  int Total() const;
  int GetPurchases() const { return purchases_; }
  int GetWages() const { return wages_; }
  int GetWaste() const { return waste_; }
 private:
  int purchases_ = 0;
  int wages_ = 0;
  int waste_ = 0;
};
