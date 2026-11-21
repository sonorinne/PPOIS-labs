#include "LunchOffer.h"
#include "MenuItem.h"
#include "UnavailableItem.h"

bool LunchOffer::IsActive(int minute) const {
  return minute >= start_ && minute < end_ && item_.GetAvailable();
}

int LunchOffer::Discount(int count) const {
  constexpr int kPercentBase = 100;
  return item_.Quote(count) * percent_ / kPercentBase;
}

int LunchOffer::Quote(int minute, int count) const {
  if (!IsActive(minute)) throw UnavailableItem();
  return item_.Quote(count) - Discount(count);
}
