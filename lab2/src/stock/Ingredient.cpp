#include "Ingredient.h"

namespace {
constexpr int kGramsPerKilogram = 1000;
constexpr int kCaloriesPortion = 100;
}


#include "InvalidQuantity.h"

int Ingredient::Cost(int grams) const {
  if (grams <= 0) throw InvalidQuantity();
  return price_ * grams / kGramsPerKilogram;
}

int Ingredient::Energy(int grams) const {
  if (grams <= 0) throw InvalidQuantity();
  return calories_ * grams / kCaloriesPortion;
}

bool Ingredient::Allowed(bool avoid_allergens) const {
  return !(avoid_allergens && allergen_);
}
