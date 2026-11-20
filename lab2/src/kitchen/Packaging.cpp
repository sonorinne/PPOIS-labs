#include "Packaging.h"
#include "Order.h"
#include "PizzaBox.h"
#include "InvalidQuantity.h"
#include "StockShortage.h"

int Packaging::RequiredBoxes(const Order& order) const {
  int count = 0;
  for (const auto& line : order.GetLines()) count += line.GetQuantity();
  return count;
}

void Packaging::Pack(const Order& order) {
  int count = RequiredBoxes(order);
  if (count <= 0 || napkins_ < count) throw StockShortage();
  boxes_.Take(count);
  napkins_ -= count;
  used_boxes_ += count;
  ++packed_orders_;
}

void Packaging::RefillNapkins(int count) {
  if (count <= 0) throw InvalidQuantity();
  napkins_ += count;
}
