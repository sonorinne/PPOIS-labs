#pragma once
#include <string>
#include <vector>
#include "StockItem.h"
class Ingredient;

/// Склад пиццерии.
class StockRoom {
 public:
  void Store(const StockItem& item);
  void Withdraw(const Ingredient& ingredient, int grams);
  int CountLow() const;
  const std::vector<StockItem>& GetItems() const { return items_; }
  int GetCapacity() const { return capacity_; }
  int GetDeliveries() const { return deliveries_; }
  int GetWithdrawals() const { return withdrawals_; }

 private:
  std::vector<StockItem> items_;
  int capacity_ = 50;
  int deliveries_ = 0;
  int withdrawals_ = 0;
};
