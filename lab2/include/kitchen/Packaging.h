#pragma once
#include <string>
#include <vector>
#include "PizzaBox.h"
class Order;

/// Упаковка заказа.
class Packaging {
 public:
  int RequiredBoxes(const Order& order) const;
  void Pack(const Order& order);
  void RefillNapkins(int count);
  const PizzaBox& GetBoxes() const { return boxes_; }
  int GetNapkins() const { return napkins_; }
  int GetPackedOrders() const { return packed_orders_; }
  int GetUsedBoxes() const { return used_boxes_; }

 private:
  PizzaBox boxes_;
  int napkins_ = 100;
  int packed_orders_ = 0;
  int used_boxes_ = 0;
};
