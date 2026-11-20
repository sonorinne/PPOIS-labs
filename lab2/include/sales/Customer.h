#pragma once
#include <string>
#include <vector>
#include "Address.h"
class Order;

/// Покупатель.
class Customer {
 public:
  Customer() = default;
  Customer(const std::string& name, const Address& address) : name_(name), address_(address) {}
  void ChooseAddress(const Address& address);
  void RequireAllergenFree();
  void RecordOrder(const Order& order);
  const std::string& GetName() const { return name_; }
  const Address& GetAddress() const { return address_; }
  bool GetAvoidAllergens() const { return avoid_allergens_; }
  int GetOrders() const { return orders_; }

 private:
  std::string name_ = "Guest";
  Address address_;
  bool avoid_allergens_ = false;
  int orders_ = 0;
};
