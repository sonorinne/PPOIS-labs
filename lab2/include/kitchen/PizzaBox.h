#pragma once
#include <string>
#include <vector>

class Pizza;

/// Коробка для пиццы.
class PizzaBox {
 public:
  bool Fits(const Pizza& pizza) const;
  int Take(int count);
  void Restock(int count);
  int GetDiameter() const { return diameter_; }
  int GetAvailable() const { return available_; }
  int GetCost() const { return cost_; }
  bool GetRecyclable() const { return recyclable_; }

 private:
  int diameter_ = 35;
  int available_ = 20;
  int cost_ = 30;
  bool recyclable_ = true;
};
