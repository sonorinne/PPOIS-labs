#include "Pizzeria.h"
#include "MenuItem.h"
#include "Menu.h"
#include "Order.h"
#include "Payment.h"
#include "CashRegister.h"
#include "BakingTask.h"
#include "Kitchen.h"
#include "InvalidOrder.h"

void Pizzeria::OpenMenu(const MenuItem& item) {
  menu_.Add(item);
  kitchen_.WarmUp();
}

Payment Pizzeria::Sell(Order& order, int tendered) {
  if (order.GetLines().empty() || order.GetConfirmed() || order.GetCancelled()) throw InvalidOrder();
  for (const auto& line : order.GetLines()) {
    const std::string& name = line.GetItem().GetName();
    const MenuItem& item = menu_.Find(name);
    item.Quote(line.GetQuantity());
  }
  Payment payment;
  payment.Capture(order, tendered);
  order.Confirm();
  cash_.Accept(payment);
  ++served_;
  return payment;
}

void Pizzeria::Bake(const BakingTask& task) {
  kitchen_.Enqueue(task);
  kitchen_.BakeNext();
}
