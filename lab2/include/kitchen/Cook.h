#pragma once
#include <string>
#include <vector>

class Recipe;
class Oven;
class BakingTask;

/// Повар.
class Cook {
 public:
  void Prepare(const Recipe& recipe);
  void Finish(BakingTask& task, Oven& oven);
  void EndShift();
  const std::string& GetName() const { return name_; }
  bool GetOnShift() const { return on_shift_; }
  int GetPrepared() const { return prepared_; }
  int GetMinutesWorked() const { return minutes_worked_; }

 private:
  std::string name_ = "Alex";
  bool on_shift_ = true;
  int prepared_ = 0;
  int minutes_worked_ = 0;
};
