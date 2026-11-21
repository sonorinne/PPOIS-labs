#pragma once

#include <cstdint>
#include <iosfwd>
#include <map>

/// Tape with integer positions and an unlimited supply of blank cells.
class Tape {
 public:
  using Position = std::int64_t;
  static constexpr char kBlank = '_';

  char Read(Position position) const;
  void Write(Position position, char symbol);
  bool operator==(const Tape& other) const;
  bool operator!=(const Tape& other) const;

  /// Write the number of nonblank cells followed by position/symbol pairs.
  friend std::ostream& operator<<(std::ostream& output, const Tape& tape);
  /// Replace the tape with the cells in the stream.
  friend std::istream& operator>>(std::istream& input, Tape& tape);

 private:
  std::map<Position, char> cells_;
};
