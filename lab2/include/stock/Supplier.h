#pragma once
#include <string>
#include "InvalidAmount.h"
#include <vector>

class Ingredient;

/// Поставщик ингредиентов.
class Supplier {
 public:
  Supplier() = default;
  Supplier(const std::string& name, int minimum, int shipping) : name_(name), minimum_(minimum), shipping_(shipping) {
    if (name.empty() || minimum < 0 || shipping < 0) throw InvalidAmount();
  }
  int Quote(const Ingredient& ingredient, int grams) const;
  void Suspend();
  void Resume();
  const std::string& GetName() const { return name_; }
  bool GetActive() const { return active_; }
  int GetMinimum() const { return minimum_; }
  int GetShipping() const { return shipping_; }

 private:
  std::string name_ = "Farm";
  bool active_ = true;
  int minimum_ = 100;
  int shipping_ = 50;
};
