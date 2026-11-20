#include "Ingredient.h"

#include "InvalidQuantity.h"

int Ingredient::Cost(int grams) const {
  if (grams <= 0) throw InvalidQuantity();
  return price_ * grams / 1000;
}

int Ingredient::Energy(int grams) const {
  if (grams <= 0) throw InvalidQuantity();
  return calories_ * grams / 100;
}

bool Ingredient::Allowed(bool avoid_allergens) const {
  return !(avoid_allergens && allergen_);
}
