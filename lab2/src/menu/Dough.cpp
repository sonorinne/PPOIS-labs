#include "Dough.h"
#include "Ingredient.h"
#include "InvalidQuantity.h"
#include "StockShortage.h"

void Dough::Rest(int minutes) {
  if (minutes <= 0) throw InvalidQuantity();
  rested_minutes_ += minutes;
}

bool Dough::Ready() const {
  return rested_minutes_ >= required_minutes_ && grams_ > 0;
}

int Dough::Use(int grams) {
  if (grams <= 0) throw InvalidQuantity();
  if (!Ready() || grams > grams_) throw StockShortage();
  grams_ -= grams;
  return flour_.Cost(grams);
}
