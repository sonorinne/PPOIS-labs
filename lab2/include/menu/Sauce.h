#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"
class Customer;

/// Порция соуса.
class Sauce {
 public:
  int Portions() const;
  void Pour(int portions);
  bool Suitable(const Customer& customer) const;
  const Ingredient& GetIngredient() const { return ingredient_; }
  int GetGrams() const { return grams_; }
  int GetServing() const { return serving_; }
  bool GetSpicy() const { return spicy_; }

 private:
  Ingredient ingredient_ = Ingredient("tomato", 20, 200, false);
  int grams_ = 500;
  int serving_ = 50;
  bool spicy_ = false;
};
