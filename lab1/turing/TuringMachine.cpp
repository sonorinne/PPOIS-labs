#include "TuringMachine.h"

#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>

Tape& TuringMachine::GetTape() { return tape_; }
Program& TuringMachine::GetProgram() { return program_; }

bool TuringMachine::Step() {
  const char read = tape_.Read(head_);
  const Rule* rule = program_.FindRule(state_, read);
  if (!rule) return false;
  if ((rule->move == 'L' && head_ == std::numeric_limits<Tape::Position>::min()) ||
      (rule->move == 'R' && head_ == std::numeric_limits<Tape::Position>::max())) {
    throw std::overflow_error("Head position is out of range");
  }
  tape_.Write(head_, rule->write);
  if (rule->move == 'L') --head_;
  if (rule->move == 'R') ++head_;
  state_ = rule->next_state;
  return true;
}

void TuringMachine::Run(std::ostream* log) {
  while (Step()) {
    if (log) WriteState(*log);
  }
}

void TuringMachine::WriteState(std::ostream& output) const {
  output << "State: " << state_ << ", head: " << head_ << '\n';
  output << tape_;
}

bool TuringMachine::operator==(const TuringMachine& other) const {
  return state_ == other.state_ && head_ == other.head_ &&
         tape_ == other.tape_ && program_ == other.program_;
}

bool TuringMachine::operator!=(const TuringMachine& other) const {
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& output, const TuringMachine& machine) {
  output << machine.state_ << ' ' << machine.head_ << '\n';
  return output << machine.tape_ << machine.program_;
}

std::istream& operator>>(std::istream& input, TuringMachine& machine) {
  TuringMachine loaded;
  if (input >> loaded.state_ >> loaded.head_ >> loaded.tape_ >> loaded.program_) {
    machine = std::move(loaded);
  }
  return input;
}
