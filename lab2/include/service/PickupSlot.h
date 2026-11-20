#pragma once
#include <string>
#include <vector>

class Order;

/// Интервал самовывоза.
class PickupSlot {
 public:
  bool Contains(int minute) const;
  void Reserve(const Order& order);
  void Release();
  int GetStart() const { return start_; }
  int GetEnd() const { return end_; }
  int GetCapacity() const { return capacity_; }
  int GetReserved() const { return reserved_; }

 private:
  int start_ = 600;
  int end_ = 630;
  int capacity_ = 5;
  int reserved_ = 0;
};
