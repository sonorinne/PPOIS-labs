#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"
class StockRoom;
class InvalidOrder;

/// Акт списания ингредиента.
class WasteRecord {
 public:
  int Cost() const;
  void Apply(StockRoom& stock);
  std::string Describe() const;
  const Ingredient& GetIngredient() const { return ingredient_; }
  int GetGrams() const { return grams_; }
  const std::string& GetReason() const { return reason_; }
  bool GetBooked() const { return booked_; }
 private:
  Ingredient ingredient_;
  int grams_ = 100;
  std::string reason_ = "expired";
  bool booked_ = false;
};
