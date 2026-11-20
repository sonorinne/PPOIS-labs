#include "Pizza.h"
#include "Recipe.h"
#include "PizzaSize.h"
#include "Topping.h"


void Pizza::AddTopping(const Topping& topping) {
  topping.Cost(1);
  toppings_.push_back(topping);
}

int Pizza::Price() const {
  int total = size_.ScalePrice(base_price_);
  for (const auto& topping : toppings_) total += topping.Cost(1);
  return total;
}

int Pizza::Margin() const {
  return Price() - recipe_.Cost();
}
