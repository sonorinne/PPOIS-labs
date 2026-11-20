#pragma once
#include <string>
#include <vector>
#include "Oven.h"
#include "BakingTask.h"
#include "Cook.h"


/// Кухня и очередь выпечки.
class Kitchen {
 public:
  void Enqueue(const BakingTask& task);
  void WarmUp();
  void BakeNext();
  const Cook& GetCook() const { return cook_; }
  const Oven& GetOven() const { return oven_; }
  const std::vector<BakingTask>& GetQueue() const { return queue_; }
  int GetCompleted() const { return completed_; }

 private:
  Cook cook_;
  Oven oven_;
  std::vector<BakingTask> queue_;
  int completed_ = 0;
};
