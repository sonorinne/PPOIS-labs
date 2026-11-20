#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"


/// Заготовка теста.
class Dough {
 public:
  void Rest(int minutes);
  bool Ready() const;
  int Use(int grams);
  const Ingredient& GetFlour() const { return flour_; }
  int GetGrams() const { return grams_; }
  int GetRestedMinutes() const { return rested_minutes_; }
  int GetRequiredMinutes() const { return required_minutes_; }

 private:
  Ingredient flour_;
  int grams_ = 300;
  int rested_minutes_ = 0;
  int required_minutes_ = 30;
};
