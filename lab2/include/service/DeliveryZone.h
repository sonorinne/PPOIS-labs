#pragma once
#include <string>
#include <vector>

class Address;
class Order;

/// Зона и тариф доставки.
class DeliveryZone {
 public:
  bool Covers(const Address& address) const;
  int Fee(const Address& address, const Order& order) const;
  int Remaining(const Address& address) const;
  const std::string& GetName() const { return name_; }
  int GetMaximum() const { return maximum_; }
  int GetPerKm() const { return per_km_; }
  int GetFreeFrom() const { return free_from_; }

 private:
  std::string name_ = "City";
  int maximum_ = 10;
  int per_km_ = 20;
  int free_from_ = 2000;
};
