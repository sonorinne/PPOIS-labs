#pragma once
#include <string>
#include <vector>
#include "Pizza.h"
class Oven;

/// Задание на выпечку.
class BakingTask {
 public:
  void Start(Oven& oven);
  void Advance(int minutes);
  bool Ready() const;
  const Pizza& GetPizza() const { return pizza_; }
  int GetElapsed() const { return elapsed_; }
  int GetRequired() const { return required_; }
  bool GetStarted() const { return started_; }

 private:
  Pizza pizza_;
  int elapsed_ = 0;
  int required_ = 8;
  bool started_ = false;
};
