#include "BakingTask.h"
#include "Pizza.h"
#include "Oven.h"
#include "InvalidQuantity.h"
#include "InvalidOrder.h"

void BakingTask::Start(Oven& oven) {
  if (started_) throw InvalidOrder();
  oven.Load(pizza_);
  started_ = true;
}

void BakingTask::Advance(int minutes) {
  if (!started_ || minutes <= 0) throw InvalidQuantity();
  elapsed_ += minutes;
}

bool BakingTask::Ready() const {
  return started_ && elapsed_ >= required_;
}
