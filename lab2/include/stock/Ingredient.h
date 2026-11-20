#pragma once
#include <string>
#include <vector>



/// Ингредиент и его пищевая ценность.
class Ingredient {
 public:
  Ingredient() = default;
  Ingredient(const std::string& name, int calories, int price, bool allergen)
      : name_(name), calories_(calories), price_(price), allergen_(allergen) {}
  int Cost(int grams) const;
  int Energy(int grams) const;
  bool Allowed(bool avoid_allergens) const;
  const std::string& GetName() const { return name_; }
  int GetCalories() const { return calories_; }
  int GetPrice() const { return price_; }
  bool GetAllergen() const { return allergen_; }

 private:
  std::string name_ = "flour";
  int calories_ = 350;
  int price_ = 100;
  bool allergen_ = true;
};

