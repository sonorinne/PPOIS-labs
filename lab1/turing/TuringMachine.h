#pragma once

#include "Program.h"
#include "Tape.h"

/// Executes rules against a tape, starting at position zero in state start.
class TuringMachine {
 public:
  Tape& GetTape();
  Program& GetProgram();
  /// Execute one rule and return false if there is no applicable rule.
  bool Step();
  /// Execute until no rule applies. Optionally write the state after each step.
  void Run(std::ostream* log = nullptr);
  void WriteState(std::ostream& output) const;

  bool operator==(const TuringMachine& other) const;
  bool operator!=(const TuringMachine& other) const;

  /// Write the state, head position, tape and transition table.
  friend std::ostream& operator<<(std::ostream& output, const TuringMachine& machine);
  /// Read the current state, head position, tape and transition table.
  friend std::istream& operator>>(std::istream& input, TuringMachine& machine);

 private:
  std::string state_ = "start";
  Tape::Position head_ = 0;
  Tape tape_;
  Program program_;
};
