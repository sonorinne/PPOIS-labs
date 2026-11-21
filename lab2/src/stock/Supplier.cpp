#include "Supplier.h"
#include "Ingredient.h"
#include "InactiveSupplier.h"

int Supplier::Quote(const Ingredient& ingredient, int grams) const {
  if (!active_) throw InactiveSupplier();
  int cost = ingredient.Cost(grams);
  return cost < minimum_ ? cost + shipping_ : cost;
}

void Supplier::Suspend() {
  if (!active_) throw InactiveSupplier();
  active_ = false;
}

void Supplier::Resume() {
  active_ = true;
}
