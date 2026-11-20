#include "Drink.h"
#include "InvalidQuantity.h"

bool Drink::CanSell(int count) const {
  return count > 0 && count <= available_;
}

int Drink::Sell(int count) {
  if (!CanSell(count)) throw InvalidQuantity();
  available_ -= count;
  return price_ * count;
}

void Drink::Restock(int count) {
  if (count <= 0) throw InvalidQuantity();
  available_ += count;
}
