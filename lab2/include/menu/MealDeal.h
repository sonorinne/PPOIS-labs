#pragma once
#include <string>
#include <vector>
#include "Pizza.h"
#include "Drink.h"
class UnavailableItem;

/// Набор из пиццы и напитка.
class MealDeal {
 public:
  int Price() const;
  bool CanServe(int count) const;
  int Sell(int count);
  const Pizza& GetPizza() const { return pizza_; }
  const Drink& GetDrink() const { return drink_; }
  int GetDiscount() const { return discount_; }
 private:
  Pizza pizza_;
  Drink drink_;
  int discount_ = 100;
};
