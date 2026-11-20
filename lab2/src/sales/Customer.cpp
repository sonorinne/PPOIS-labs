#include "Customer.h"
#include "Address.h"
#include "Order.h"
#include "InvalidOrder.h"

void Customer::ChooseAddress(const Address& address) {
  address.Validate();
  address_ = address;
}

void Customer::RequireAllergenFree() {
  avoid_allergens_ = true;
}

void Customer::RecordOrder(const Order& order) {
  if (order.GetLines().empty()) throw InvalidOrder();
  ++orders_;
}
