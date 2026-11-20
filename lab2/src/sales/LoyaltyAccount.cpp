#include "LoyaltyAccount.h"
#include "Customer.h"
#include "Payment.h"
#include "InvalidAmount.h"
#include "InsufficientPayment.h"

namespace {
constexpr int kCentsPerPoint = 100;
}


void LoyaltyAccount::Earn(const Payment& payment) {
  if (!payment.GetCaptured()) throw InsufficientPayment();
  int bonus = payment.GetAmount() / kCentsPerPoint;
  points_ += bonus;
  earned_ += bonus;
}

int LoyaltyAccount::Redeem(int points) {
  if (points <= 0) throw InvalidAmount();
  if (points > points_) throw InsufficientPayment();
  points_ -= points;
  spent_ += points;
  return points;
}

void LoyaltyAccount::TransferTo(LoyaltyAccount& target, int points) {
  if (&target == this) throw InvalidAmount();
  Redeem(points);
  target.points_ += points;
}
