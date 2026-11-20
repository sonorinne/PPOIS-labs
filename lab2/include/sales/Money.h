#pragma once
#include <string>

/// Сумма в белорусских рублях, хранимая в копейках.
class Money {
 public:
  static Money Parse(const std::string& text);
  static Money FromKopecks(int kopecks);
  std::string ToString() const;
  int ToKopecks() const { return kopecks_; }
 private:
  static int ReadPart(const std::string& text);
  static constexpr int kKopecksPerRuble = 100;
  int kopecks_ = 0;
};
