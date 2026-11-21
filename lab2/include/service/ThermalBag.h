#pragma once
#include <string>
#include <vector>
#include "Pizza.h"
class InvalidOrder;
class UnavailableItem;

/// Термосумка для готовых пицц.
class ThermalBag {
 public:
  void Load(const Pizza& pizza);
  Pizza Unload();
  void Clean();
  const std::vector<Pizza>& GetPizzas() const { return pizzas_; }
  int GetCapacity() const { return capacity_; }
  bool GetClean() const { return clean_; }
 private:
  std::vector<Pizza> pizzas_;
  int capacity_ = 3;
  bool clean_ = true;
};
