#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"
#include "Supplier.h"


/// Строка закупки.
class PurchaseLine {
 public:
  PurchaseLine() = default;
  PurchaseLine(const Ingredient& ingredient, const Supplier& supplier, int grams) : ingredient_(ingredient), supplier_(supplier), grams_(grams) {}
  int Total() const;
  void Receive(int grams);
  int Outstanding() const;
  const Ingredient& GetIngredient() const { return ingredient_; }
  const Supplier& GetSupplier() const { return supplier_; }
  int GetGrams() const { return grams_; }
  int GetReceived() const { return received_; }

 private:
  Ingredient ingredient_;
  Supplier supplier_;
  int grams_ = 1000;
  int received_ = 0;
};
