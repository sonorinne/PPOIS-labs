#include "Money.h"
#include "InvalidAmount.h"
#include <limits>

int Money::ReadPart(const std::string& text) {
  if (text.empty()) throw InvalidAmount();
  int value = 0;
  for (char symbol : text) {
    if (symbol < '0' || symbol > '9') throw InvalidAmount();
    int digit = symbol - '0';
    if (value > (std::numeric_limits<int>::max() - digit) / 10) throw InvalidAmount();
    value = value * 10 + digit;
  }
  return value;
}

Money Money::Parse(const std::string& text) {
  const auto separator = text.find_first_of(".,");
  int rubles = ReadPart(text.substr(0, separator));
  int fraction = 0;
  if (separator != std::string::npos) {
    std::string digits = text.substr(separator + 1);
    if (digits.size() > 2) throw InvalidAmount();
    fraction = ReadPart(digits);
    if (digits.size() == 1) fraction *= 10;
  }
  const int maximum = std::numeric_limits<int>::max();
  if (rubles > maximum / kKopecksPerRuble) throw InvalidAmount();
  int kopecks = rubles * kKopecksPerRuble;
  if (fraction > maximum - kopecks) throw InvalidAmount();
  return FromKopecks(kopecks + fraction);
}

Money Money::FromKopecks(int kopecks) {
  if (kopecks < 0) throw InvalidAmount();
  Money amount;
  amount.kopecks_ = kopecks;
  return amount;
}

std::string Money::ToString() const {
  int rubles = kopecks_ / kKopecksPerRuble;
  int fraction = kopecks_ % kKopecksPerRuble;
  std::string digits = std::to_string(fraction);
  if (fraction < 10) digits = "0" + digits;
  return std::to_string(rubles) + "." + digits + " BYN";
}
