#include "Topping.h"
#include "Ingredient.h"
#include "Customer.h"
#include "InvalidQuantity.h"
#include "UnavailableItem.h"

int Topping::Cost(int count) const {
  if (!available_) throw UnavailableItem();
  if (count <= 0) throw InvalidQuantity();
  return (ingredient_.Cost(grams_) + surcharge_) * count;
}

void Topping::StopSales() {
  available_ = false;
}

bool Topping::CanServe(const Customer& customer) const {
  return available_ && ingredient_.Allowed(customer.GetAvoidAllergens());
}
