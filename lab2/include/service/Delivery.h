#pragma once
#include <string>
#include <vector>
#include "Address.h"
#include "Order.h"
class Courier;
class DeliveryZone;

/// Доставка оплаченного заказа.
class Delivery {
 public:
  void Accept(const Order& order, const Address& address);
  void Dispatch(Courier& courier, const DeliveryZone& zone);
  void Complete(Courier& courier);
  const Order& GetOrder() const { return order_; }
  const Address& GetAddress() const { return address_; }
  bool GetDispatched() const { return dispatched_; }
  bool GetDelivered() const { return delivered_; }

 private:
  Order order_;
  Address address_;
  bool dispatched_ = false;
  bool delivered_ = false;
};
