#include "Courier.h"
#include "Address.h"
#include "UnavailableCourier.h"

namespace {
constexpr int kMinutesPerKilometer = 5;
constexpr int kHandoverMinutes = 10;
}


void Courier::Assign(const Address& address) {
  if (busy_) throw UnavailableCourier();
  address.Validate();
  busy_ = true;
}

void Courier::Complete(const Address& address) {
  if (!busy_) throw UnavailableCourier();
  address.Validate();
  distance_ += address.GetDistance();
  ++deliveries_;
  busy_ = false;
}

int Courier::Estimate(const Address& address) const {
  address.Validate();
  return address.GetDistance() * kMinutesPerKilometer + kHandoverMinutes;
}
