#pragma once
#include <string>
#include <vector>
#include "Customer.h"
class Table;

/// Бронирование стола.
class Reservation {
 public:
  void CheckIn(Table& table);
  void Postpone(int minutes);
  void Cancel();
  const Customer& GetCustomer() const { return customer_; }
  int GetGuests() const { return guests_; }
  int GetMinute() const { return minute_; }
  bool GetActive() const { return active_; }

 private:
  Customer customer_;
  int guests_ = 2;
  int minute_ = 600;
  bool active_ = true;
};
