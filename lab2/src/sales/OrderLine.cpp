#include "OrderLine.h"
#include "MenuItem.h"
#include "PizzaBox.h"
#include "InvalidQuantity.h"
#include "InvalidOrder.h"

void OrderLine::Increase(int count) {
  if (count <= 0 || packed_) throw InvalidQuantity();
  item_.Quote(quantity_ + count);
  quantity_ += count;
}

int OrderLine::Total() const {
  return item_.Quote(quantity_);
}

void OrderLine::Pack(const PizzaBox& box) {
  if (packed_ || !box.Fits(item_.GetPizza())) throw InvalidOrder();
  packed_ = true;
}
