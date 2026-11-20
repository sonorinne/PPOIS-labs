#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"
class StockRoom;

/// Количество ингредиента для одной пиццы.
class RecipePart {
 public:
  RecipePart() = default;
  RecipePart(const Ingredient& ingredient, int grams) : ingredient_(ingredient), grams_(grams) {}
  int Required(int count) const;
  int Cost(int count) const;
  void TakeFrom(StockRoom& stock, int count) const;
  const Ingredient& GetIngredient() const { return ingredient_; }
  int GetGrams() const { return grams_; }
  int GetLossPercent() const { return loss_percent_; }
  const std::string& GetStage() const { return stage_; }

 private:
  Ingredient ingredient_;
  int grams_ = 200;
  int loss_percent_ = 5;
  std::string stage_ = "dough";
};
