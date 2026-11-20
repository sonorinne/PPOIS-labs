#include "PizzaBox.h"
#include "Pizza.h"
#include "InvalidQuantity.h"
#include "StockShortage.h"

bool PizzaBox::Fits(const Pizza& pizza) const {
  return pizza.GetSize().Fits(diameter_);
}

int PizzaBox::Take(int count) {
  if (count <= 0) throw InvalidQuantity();
  if (count > available_) throw StockShortage();
  available_ -= count;
  return count * cost_;
}

void PizzaBox::Restock(int count) {
  if (count <= 0) throw InvalidQuantity();
  available_ += count;
}
