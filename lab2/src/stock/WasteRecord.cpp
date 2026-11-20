#include "WasteRecord.h"
#include "Ingredient.h"
#include "StockRoom.h"
#include "InvalidOrder.h"

int WasteRecord::Cost() const {
  return ingredient_.Cost(grams_);
}

void WasteRecord::Apply(StockRoom& stock) {
  if (booked_) throw InvalidOrder();
  stock.Withdraw(ingredient_, grams_);
  booked_ = true;
}

std::string WasteRecord::Describe() const {
  return ingredient_.GetName() + ": " + std::to_string(grams_) + " g, " + reason_;
}
