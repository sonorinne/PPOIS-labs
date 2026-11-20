#include "Review.h"
#include "Customer.h"
#include "InvalidQuantity.h"
#include "InvalidOrder.h"

void Review::Rate(int stars) {
  if (published_ || stars < 1 || stars > 5) throw InvalidQuantity();
  stars_ = stars;
}

void Review::Write(const std::string& text) {
  if (published_ || text.empty()) throw InvalidOrder();
  text_ = text;
}

void Review::Publish() {
  if (published_ || text_.empty()) throw InvalidOrder();
  published_ = true;
}
