#pragma once
#include <string>
#include <vector>
#include "Customer.h"
class Payment;

/// Бонусный счёт клиента.
class LoyaltyAccount {
 public:
  void Earn(const Payment& payment);
  int Redeem(int points);
  void TransferTo(LoyaltyAccount& target, int points);
  const Customer& GetOwner() const { return owner_; }
  int GetPoints() const { return points_; }
  int GetEarned() const { return earned_; }
  int GetSpent() const { return spent_; }

 private:
  Customer owner_;
  int points_ = 0;
  int earned_ = 0;
  int spent_ = 0;
};
