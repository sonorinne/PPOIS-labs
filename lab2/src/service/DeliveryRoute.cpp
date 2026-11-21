#include "DeliveryRoute.h"
#include "Address.h"
#include "InvalidOrder.h"

void DeliveryRoute::AddStop(const Address& address) {
  if (finished_ || static_cast<int>(stops_.size()) >= capacity_) throw InvalidOrder();
  address.Validate();
  stops_.push_back(address);
}

int DeliveryRoute::TotalDistance() const {
  int total = 0;
  for (const auto& stop : stops_) total += stop.GetDistance();
  return total;
}

void DeliveryRoute::Finish() {
  if (finished_ || stops_.empty()) throw InvalidOrder();
  finished_ = true;
}
