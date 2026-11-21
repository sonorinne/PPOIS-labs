#pragma once
#include <string>
#include <vector>
#include "Cook.h"


/// Учёт смены повара.
class WorkShift {
 public:
  void Finish(int minute);
  int Duration() const;
  int Salary() const;
  const Cook& GetCook() const { return cook_; }
  int GetStart() const { return start_; }
  int GetEnd() const { return end_; }
  int GetRate() const { return rate_; }

 private:
  Cook cook_;
  int start_ = 600;
  int end_ = 0;
  int rate_ = 500;
};
