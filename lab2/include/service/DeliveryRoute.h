#pragma once
#include <string>
#include <vector>
#include "Address.h"
class InvalidOrder;

/// План выездов по адресам.
class DeliveryRoute {
 public:
  void AddStop(const Address& address);
  int TotalDistance() const;
  void Finish();
  const std::vector<Address>& GetStops() const { return stops_; }
  int GetCapacity() const { return capacity_; }
  bool GetFinished() const { return finished_; }
 private:
  std::vector<Address> stops_;
  int capacity_ = 5;
  bool finished_ = false;
};
