#include "Cook.h"
#include "Recipe.h"
#include "Oven.h"
#include "BakingTask.h"
#include "InvalidOrder.h"

void Cook::Prepare(const Recipe& recipe) {
  if (!on_shift_) throw InvalidOrder();
  recipe.RequiredGrams();
  ++prepared_;
  minutes_worked_ += recipe.GetBakeMinutes();
}

void Cook::Finish(BakingTask& task, Oven& oven) {
  if (!on_shift_ || !task.Ready()) throw InvalidOrder();
  oven.Unload();
}

void Cook::EndShift() {
  on_shift_ = false;
}
