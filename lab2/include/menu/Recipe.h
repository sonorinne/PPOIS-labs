#pragma once
#include <string>
#include <vector>
#include "RecipePart.h"


/// Рецепт пиццы.
class Recipe {
 public:
  Recipe() = default;
  explicit Recipe(const std::string& name) : name_(name) {}
  void Add(const RecipePart& part);
  int Cost() const;
  int RequiredGrams() const;
  const std::string& GetName() const { return name_; }
  const std::vector<RecipePart>& GetParts() const { return parts_; }
  int GetBakeMinutes() const { return bake_minutes_; }
  int GetPortions() const { return portions_; }

 private:
  std::string name_ = "Classic";
  std::vector<RecipePart> parts_;
  int bake_minutes_ = 8;
  int portions_ = 1;
};
