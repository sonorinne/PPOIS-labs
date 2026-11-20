#pragma once
#include <string>
#include <vector>
#include "MenuItem.h"
class UnavailableItem;

/// Скидка в заданное время.
class LunchOffer {
 public:
  bool IsActive(int minute) const;
  int Discount(int count) const;
  int Quote(int minute, int count) const;
  const MenuItem& GetItem() const { return item_; }
  int GetStart() const { return start_; }
  int GetEnd() const { return end_; }
  int GetPercent() const { return percent_; }
 private:
  MenuItem item_;
  int start_ = 720;
  int end_ = 900;
  int percent_ = 15;
};
