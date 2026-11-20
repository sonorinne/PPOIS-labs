#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"
class PurchaseLine;

/// Остаток конкретного ингредиента.
class StockItem {
 public:
  StockItem() = default;
  explicit StockItem(const Ingredient& ingredient) : ingredient_(ingredient) {}
  void Receive(const PurchaseLine& line);
  void Consume(int grams);
  void Discard(int grams);
  void Merge(const StockItem& other);
  const Ingredient& GetIngredient() const { return ingredient_; }
  int GetGrams() const { return grams_; }
  int GetMinimum() const { return minimum_; }
  int GetWasted() const { return wasted_; }

 private:
  Ingredient ingredient_;
  int grams_ = 0;
  int minimum_ = 500;
  int wasted_ = 0;
};
