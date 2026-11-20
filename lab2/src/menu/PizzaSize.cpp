#include "PizzaSize.h"

namespace {
constexpr int kPercentBase = 100;
}


#include "InvalidAmount.h"
#include "InvalidQuantity.h"

int PizzaSize::ScalePrice(int base) const {
  if (base < 0) throw InvalidAmount();
  return base * price_percent_ / kPercentBase;
}

bool PizzaSize::Fits(int oven_diameter) const {
  return diameter_ <= oven_diameter;
}

int PizzaSize::SliceWeight(int grams) const {
  if (grams <= 0) throw InvalidQuantity();
  return grams / slices_;
}
