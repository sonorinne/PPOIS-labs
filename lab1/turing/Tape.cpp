#include "Tape.h"

#include <istream>
#include <ostream>
#include <utility>

char Tape::Read(Position position) const {
  const auto cell = cells_.find(position);
  if (cell == cells_.end()) return kBlank;
  return cell->second;
}

void Tape::Write(Position position, char symbol) {
  if (symbol == kBlank) {
    cells_.erase(position);
  } else {
    cells_[position] = symbol;
  }
}

bool Tape::operator==(const Tape& other) const {
  return cells_ == other.cells_;
}

bool Tape::operator!=(const Tape& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& output, const Tape& tape) {
  output << tape.cells_.size() << '\n';
  for (const auto& [position, symbol] : tape.cells_) {
    output << position << ' ' << symbol << '\n';
  }
  return output;
}

std::istream& operator>>(std::istream& input, Tape& tape) {
  int count = 0;
  if (!(input >> count)) return input;
  if (count < 0) {
    input.setstate(std::ios::failbit);
    return input;
  }
  Tape loaded;
  for (int index = 0; index < count; ++index) {
    Tape::Position position = 0;
    char symbol = Tape::kBlank;
    if (!(input >> position >> symbol)) return input;
    loaded.Write(position, symbol);
  }
  tape = std::move(loaded);
  return input;
}
