#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"
class Customer;

/// Дополнительная начинка.
class Topping {
 public:
  int Cost(int count) const;
  void StopSales();
  bool CanServe(const Customer& customer) const;
  const Ingredient& GetIngredient() const { return ingredient_; }
  int GetGrams() const { return grams_; }
  int GetSurcharge() const { return surcharge_; }
  bool GetAvailable() const { return available_; }

 private:
  Ingredient ingredient_ = Ingredient("cheese", 300, 300, true);
  int grams_ = 30;
  int surcharge_ = 80;
  bool available_ = true;
};
