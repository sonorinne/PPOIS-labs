#include "Recipe.h"
#include "RecipePart.h"
#include "EmptyRecipe.h"

void Recipe::Add(const RecipePart& part) {
  parts_.push_back(part);
}

int Recipe::Cost() const {
  if (parts_.empty()) throw EmptyRecipe();
  int total = 0;
  for (const auto& part : parts_) total += part.Cost(portions_);
  return total;
}

int Recipe::RequiredGrams() const {
  if (parts_.empty()) throw EmptyRecipe();
  int total = 0;
  for (const auto& part : parts_) total += part.Required(portions_);
  return total;
}
