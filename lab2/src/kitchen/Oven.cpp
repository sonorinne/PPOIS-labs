#include "Oven.h"
#include "Pizza.h"
#include "InvalidQuantity.h"
#include "UnavailableOven.h"

void Oven::Heat(int degrees) {
  if (degrees <= 0) throw InvalidQuantity();
  temperature_ += degrees;
}

void Oven::Load(const Pizza& pizza) {
  if (occupied_ || temperature_ < required_temperature_ || !pizza.GetSize().Fits(diameter_)) throw UnavailableOven();
  occupied_ = true;
}

void Oven::Unload() {
  if (!occupied_) throw UnavailableOven();
  occupied_ = false;
}
