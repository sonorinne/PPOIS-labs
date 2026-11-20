#include "PurchaseLine.h"
#include "Ingredient.h"
#include "Supplier.h"
#include "InvalidQuantity.h"

int PurchaseLine::Total() const {
  return supplier_.Quote(ingredient_, grams_);
}

void PurchaseLine::Receive(int grams) {
  if (grams <= 0 || grams > grams_ - received_) throw InvalidQuantity();
  received_ += grams;
}

int PurchaseLine::Outstanding() const {
  return grams_ - received_;
}
