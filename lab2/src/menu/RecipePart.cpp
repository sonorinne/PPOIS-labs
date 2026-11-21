#include "RecipePart.h"
#include "Ingredient.h"
#include "StockRoom.h"
#include "InvalidQuantity.h"

namespace {
constexpr int kPercentBase = 100;
}


int RecipePart::Required(int count) const {
  if (count <= 0) throw InvalidQuantity();
  return grams_ * count * (kPercentBase + loss_percent_) / kPercentBase;
}

int RecipePart::Cost(int count) const {
  return ingredient_.Cost(Required(count));
}

void RecipePart::TakeFrom(StockRoom& stock, int count) const {
  stock.Withdraw(ingredient_, Required(count));
}
