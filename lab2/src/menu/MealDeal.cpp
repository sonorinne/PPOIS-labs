#include "MealDeal.h"
#include "Pizza.h"
#include "UnavailableItem.h"
#include "Drink.h"

int MealDeal::Price() const {
  return pizza_.Price() + drink_.GetPrice() - discount_;
}

bool MealDeal::CanServe(int count) const {
  return drink_.CanSell(count);
}

int MealDeal::Sell(int count) {
  if (!CanServe(count)) throw UnavailableItem();
  drink_.Sell(count);
  return Price() * count;
}
