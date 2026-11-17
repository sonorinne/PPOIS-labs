#include "Program.h"

#include <istream>
#include <ostream>

bool Rule::operator==(const Rule& other) const {
  return next_state == other.next_state && write == other.write &&
         move == other.move;
}

bool Program::AddRule(const std::string& state, char read, const Rule& rule) {
  if (rule.move != 'L' && rule.move != 'R' && rule.move != 'S') return false;
  rules_[{state, read}] = rule;
  return true;
}

bool Program::RemoveRule(const std::string& state, char read) {
  return rules_.erase({state, read}) != 0;
}

const Rule* Program::FindRule(const std::string& state, char read) const {
  const auto found = rules_.find({state, read});
  if (found == rules_.end()) return nullptr;
  return &found->second;
}

bool Program::operator==(const Program& other) const {
  return rules_ == other.rules_;
}

bool Program::operator!=(const Program& other) const {
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& output, const Program& program) {
  output << program.rules_.size() << '\n';
  for (const auto& [key, rule] : program.rules_) {
    output << key.first << ' ' << key.second << ' ' << rule.next_state << ' '
           << rule.write << ' ' << rule.move << '\n';
  }
  return output;
}

std::istream& operator>>(std::istream& input, Program& program) {
  int count = 0;
  if (!(input >> count)) return input;
  if (count < 0) {
    input.setstate(std::ios::failbit);
    return input;
  }
  Program loaded;
  for (int index = 0; index < count; ++index) {
    std::string state;
    char read = '\0';
    Rule rule{};
    if (!(input >> state >> read >> rule.next_state >> rule.write >> rule.move)) return input;
    if (!loaded.AddRule(state, read, rule)) {
      input.setstate(std::ios::failbit);
      return input;
    }
  }
  program = std::move(loaded);
  return input;
}
