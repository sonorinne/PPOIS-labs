#include "ExpenseBook.h"
#include "PurchaseOrder.h"
#include "WorkShift.h"
#include "InvalidOrder.h"
#include "WasteRecord.h"

void ExpenseBook::RecordPurchase(const PurchaseOrder& purchase) {
  if (!purchase.GetClosed()) throw InvalidOrder();
  purchases_ += purchase.Total();
}

void ExpenseBook::RecordShift(const WorkShift& shift) {
  wages_ += shift.Salary();
}

void ExpenseBook::RecordWaste(const WasteRecord& record) {
  if (!record.GetBooked()) throw InvalidOrder();
  waste_ += record.Cost();
}

int ExpenseBook::Total() const {
  return purchases_ + wages_ + waste_;
}
