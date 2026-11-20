#pragma once
#include <string>
#include <vector>
#include "MenuItem.h"
class PizzaBox;

/// Строка заказа.
class OrderLine {
 public:
  OrderLine() = default;
  OrderLine(const MenuItem& item, int quantity) : item_(item), quantity_(quantity) {}
  void Increase(int count);
  int Total() const;
  void Pack(const PizzaBox& box);
  const MenuItem& GetItem() const { return item_; }
  int GetQuantity() const { return quantity_; }
  const std::string& GetComment() const { return comment_; }
  bool GetPacked() const { return packed_; }

 private:
  MenuItem item_;
  int quantity_ = 1;
  std::string comment_ = "";
  bool packed_ = false;
};
