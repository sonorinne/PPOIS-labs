#include "Kitchen.h"
#include "Oven.h"
#include "BakingTask.h"
#include "Cook.h"
#include "InvalidOrder.h"

void Kitchen::Enqueue(const BakingTask& task) {
  queue_.push_back(task);
}

void Kitchen::WarmUp() {
  oven_.Heat(oven_.GetRequiredTemperature());
}

void Kitchen::BakeNext() {
  if (queue_.empty()) throw InvalidOrder();
  BakingTask task = queue_.front();
  task.Start(oven_);
  task.Advance(task.GetRequired());
  cook_.Finish(task, oven_);
  queue_.erase(queue_.begin());
  ++completed_;
}
