#pragma once
#include <string>
#include <vector>
#include "Recipe.h"
#include "PizzaSize.h"
#include "Topping.h"


/// Пицца с рецептом и размером.
class Pizza {
 public:
  Pizza() { recipe_.Add(RecipePart{}); }
  Pizza(const Recipe& recipe, const PizzaSize& size, int price) : recipe_(recipe), size_(size), base_price_(price) {}
  void AddTopping(const Topping& topping);
  int Price() const;
  int Margin() const;
  const Recipe& GetRecipe() const { return recipe_; }
  const PizzaSize& GetSize() const { return size_; }
  const std::vector<Topping>& GetToppings() const { return toppings_; }
  int GetBasePrice() const { return base_price_; }

 private:
  Recipe recipe_;
  PizzaSize size_;
  std::vector<Topping> toppings_;
  int base_price_ = 600;
};
