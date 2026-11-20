#pragma once
#include <string>
#include <vector>



/// Размер и количество кусков.
class PizzaSize {
 public:
  PizzaSize() = default;
  PizzaSize(const std::string& name, int diameter, int slices, int percent)
      : name_(name), diameter_(diameter), slices_(slices), price_percent_(percent) {}
  int ScalePrice(int base) const;
  bool Fits(int oven_diameter) const;
  int SliceWeight(int grams) const;
  const std::string& GetName() const { return name_; }
  int GetDiameter() const { return diameter_; }
  int GetSlices() const { return slices_; }
  int GetPricePercent() const { return price_percent_; }

 private:
  std::string name_ = "medium";
  int diameter_ = 30;
  int slices_ = 8;
  int price_percent_ = 100;
};

