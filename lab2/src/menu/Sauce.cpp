#include "Sauce.h"
#include "Ingredient.h"
#include "Customer.h"
#include "InvalidQuantity.h"
#include "StockShortage.h"

int Sauce::Portions() const {
  return grams_ / serving_;
}

void Sauce::Pour(int portions) {
  if (portions <= 0) throw InvalidQuantity();
  if (portions > Portions()) throw StockShortage();
  grams_ -= portions * serving_;
}

bool Sauce::Suitable(const Customer& customer) const {
  return ingredient_.Allowed(customer.GetAvoidAllergens()) && !spicy_;
}
