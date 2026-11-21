#include "WorkShift.h"
#include "Cook.h"
#include "InvalidQuantity.h"
#include "InvalidOrder.h"

namespace {
constexpr int kMinutesPerHour = 60;
}


void WorkShift::Finish(int minute) {
  if (end_ != 0 || minute <= start_) throw InvalidQuantity();
  end_ = minute;
  cook_.EndShift();
}

int WorkShift::Duration() const {
  if (end_ == 0) throw InvalidOrder();
  return end_ - start_;
}

int WorkShift::Salary() const {
  return Duration() * rate_ / kMinutesPerHour;
}
