#include "MenuItem.h"
#include "Pizza.h"
#include "InvalidQuantity.h"
#include "UnavailableItem.h"

int MenuItem::Quote(int count) const {
  if (!available_) throw UnavailableItem();
  if (count <= 0) throw InvalidQuantity();
  return pizza_.Price() * count;
}

void MenuItem::Sell(int count) {
  Quote(count);
  sold_ += count;
}

void MenuItem::StopSales() {
  available_ = false;
}
