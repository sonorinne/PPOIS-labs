#pragma once
#include <string>
#include <vector>
#include "Pizza.h"


/// Позиция меню.
class MenuItem {
 public:
  MenuItem() = default;
  MenuItem(const Pizza& pizza, const std::string& name) : pizza_(pizza), name_(name) {}
  int Quote(int count) const;
  void Sell(int count);
  void StopSales();
  const Pizza& GetPizza() const { return pizza_; }
  const std::string& GetName() const { return name_; }
  bool GetAvailable() const { return available_; }
  int GetSold() const { return sold_; }

 private:
  Pizza pizza_;
  std::string name_ = "Classic";
  bool available_ = true;
  int sold_ = 0;
};
