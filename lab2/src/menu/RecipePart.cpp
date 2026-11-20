#include "RecipePart.h"
#include "Ingredient.h"
#include "StockRoom.h"
#include "InvalidQuantity.h"

int RecipePart::Required(int count) const {
  if (count <= 0) throw InvalidQuantity();
  return grams_ * count * (100 + loss_percent_) / 100;
}

int RecipePart::Cost(int count) const {
  return ingredient_.Cost(Required(count));
}

void RecipePart::TakeFrom(StockRoom& stock, int count) const {
  stock.Withdraw(ingredient_, Required(count));
}
