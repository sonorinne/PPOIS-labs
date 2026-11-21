#pragma once

#include <iosfwd>
#include <map>
#include <string>
#include <utility>

/// Action taken when a state and the symbol under the head match a rule.
struct Rule {
  std::string next_state;
  char write;
  char move;

  bool operator==(const Rule& other) const;
};

/// Transition table indexed by current state and symbol.
class Program {
 public:
  /// Add or replace a rule. Directions are L, R and S (stay).
  bool AddRule(const std::string& state, char read, const Rule& rule);
  bool RemoveRule(const std::string& state, char read);
  const Rule* FindRule(const std::string& state, char read) const;
  bool operator==(const Program& other) const;
  bool operator!=(const Program& other) const;

  /// Write a count and rules in the form: state read next_state write move.
  friend std::ostream& operator<<(std::ostream& output, const Program& program);
  /// Replace the transition table with rules from the stream.
  friend std::istream& operator>>(std::istream& input, Program& program);

 private:
  std::map<std::pair<std::string, char>, Rule> rules_;
};
