#include "PickupSlot.h"
#include "Order.h"
#include "InvalidReservation.h"

bool PickupSlot::Contains(int minute) const {
  return minute >= start_ && minute < end_;
}

void PickupSlot::Reserve(const Order& order) {
  if (!order.GetConfirmed() || reserved_ >= capacity_) throw InvalidReservation();
  ++reserved_;
}

void PickupSlot::Release() {
  if (reserved_ == 0) throw InvalidReservation();
  --reserved_;
}
