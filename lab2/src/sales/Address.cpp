#include "Address.h"

#include "InvalidAddress.h"

void Address::Validate() const {
  if (street_.empty() || house_ <= 0 || distance_ < 0) throw InvalidAddress();
}

bool Address::InRange(int maximum) const {
  Validate();
  return distance_ <= maximum;
}

std::string Address::Label() const {
  Validate();
  return street_ + " " + std::to_string(house_) + " / " + entrance_;
}
