#include "ThermalBag.h"
#include "Pizza.h"
#include "InvalidOrder.h"
#include "UnavailableItem.h"

void ThermalBag::Load(const Pizza& pizza) {
  if (!clean_ || static_cast<int>(pizzas_.size()) >= capacity_) throw UnavailableItem();
  pizzas_.push_back(pizza);
}

Pizza ThermalBag::Unload() {
  if (pizzas_.empty()) throw UnavailableItem();
  Pizza pizza = pizzas_.back();
  pizzas_.pop_back();
  clean_ = false;
  return pizza;
}

void ThermalBag::Clean() {
  if (!pizzas_.empty()) throw InvalidOrder();
  clean_ = true;
}
