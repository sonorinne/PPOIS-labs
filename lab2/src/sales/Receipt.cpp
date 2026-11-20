#include "Receipt.h"
#include "Order.h"
#include "Payment.h"
#include "InvalidAmount.h"
#include "InvalidOrder.h"

void Receipt::Validate() const {
  if (order_.GetLines().empty() || !payment_.GetCaptured() || payment_.GetRefunded()) throw InvalidOrder();
  if (order_.Total() != payment_.GetAmount()) throw InvalidAmount();
}

int Receipt::Total() const {
  Validate();
  return payment_.Net();
}

std::string Receipt::Text() const {
  return shop_ + ", total: " + std::to_string(Total());
}
