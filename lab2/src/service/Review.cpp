#include "Review.h"
#include "Customer.h"
#include "InvalidQuantity.h"
#include "InvalidOrder.h"

namespace {
constexpr int kMinimumStars = 1;
constexpr int kMaximumStars = 5;
}


void Review::Rate(int stars) {
  if (published_ || stars < kMinimumStars || stars > kMaximumStars) throw InvalidQuantity();
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
