#include "StockRoom.h"
#include "Ingredient.h"
#include "StockItem.h"
#include "StockShortage.h"
#include "UnavailableItem.h"

void StockRoom::Store(const StockItem& item) {
  for (auto& existing : items_) {
    if (existing.GetIngredient().GetName() == item.GetIngredient().GetName()) {
      existing.Merge(item);
      ++deliveries_;
      return;
    }
  }
  if (static_cast<int>(items_.size()) >= capacity_) throw StockShortage();
  items_.push_back(item);
  ++deliveries_;
}

void StockRoom::Withdraw(const Ingredient& ingredient, int grams) {
  for (auto& item : items_) {
    if (item.GetIngredient().GetName() == ingredient.GetName()) {
      item.Consume(grams);
      ++withdrawals_;
      return;
    }
  }
  throw UnavailableItem();
}

int StockRoom::CountLow() const {
  int count = 0;
  for (const auto& item : items_) {
    if (item.GetGrams() < item.GetMinimum()) ++count;
  }
  return count;
}
