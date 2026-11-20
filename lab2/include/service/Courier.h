#pragma once
#include <string>
#include <vector>

class Address;

/// Курьер.
class Courier {
 public:
  void Assign(const Address& address);
  void Complete(const Address& address);
  int Estimate(const Address& address) const;
  const std::string& GetName() const { return name_; }
  bool GetBusy() const { return busy_; }
  int GetDistance() const { return distance_; }
  int GetDeliveries() const { return deliveries_; }

 private:
  std::string name_ = "Sam";
  bool busy_ = false;
  int distance_ = 0;
  int deliveries_ = 0;
};
