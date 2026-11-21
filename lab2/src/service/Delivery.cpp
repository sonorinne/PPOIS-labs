#include "Delivery.h"
#include "Address.h"
#include "Order.h"
#include "Courier.h"
#include "DeliveryZone.h"
#include "InvalidAddress.h"
#include "InvalidOrder.h"

void Delivery::Accept(const Order& order, const Address& address) {
  if (dispatched_ || order.GetCancelled() || !order.GetConfirmed()) throw InvalidOrder();
  address.Validate();
  order_ = order;
  address_ = address;
}

void Delivery::Dispatch(Courier& courier, const DeliveryZone& zone) {
  if (dispatched_ || !order_.GetConfirmed()) throw InvalidOrder();
  if (!zone.Covers(address_)) throw InvalidAddress();
  courier.Assign(address_);
  dispatched_ = true;
}

void Delivery::Complete(Courier& courier) {
  if (!dispatched_ || delivered_) throw InvalidOrder();
  courier.Complete(address_);
  delivered_ = true;
}
