#include "Coupon.h"
#include "Customer.h"
#include "Order.h"
#include "InvalidOrder.h"

int Coupon::Discount(const Order& order) const {
  if (used_ || order.Subtotal() < minimum_) throw InvalidOrder();
  return order.Subtotal() * percent_ / 100;
}

void Coupon::Redeem(Order& order) {
  int discount = Discount(order);
  order.ApplyDiscount(discount);
  used_ = true;
}

bool Coupon::Eligible(const Customer& customer) const {
  return !used_ && customer.GetOrders() == 0;
}
