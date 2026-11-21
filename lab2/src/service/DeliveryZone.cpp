#include "DeliveryZone.h"
#include "Address.h"
#include "Order.h"
#include "InvalidAddress.h"

bool DeliveryZone::Covers(const Address& address) const {
  return address.InRange(maximum_);
}

int DeliveryZone::Fee(const Address& address, const Order& order) const {
  if (!Covers(address)) throw InvalidAddress();
  return order.Total() >= free_from_ ? 0 : address.GetDistance() * per_km_;
}

int DeliveryZone::Remaining(const Address& address) const {
  if (!Covers(address)) throw InvalidAddress();
  return maximum_ - address.GetDistance();
}
