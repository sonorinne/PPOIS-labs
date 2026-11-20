#pragma once
#include <string>
#include <vector>



/// Адрес доставки.
class Address {
 public:
  Address() = default;
  Address(const std::string& street, int house, int distance, const std::string& entrance)
      : street_(street), house_(house), distance_(distance), entrance_(entrance) {}
  void Validate() const;
  bool InRange(int maximum) const;
  std::string Label() const;
  const std::string& GetStreet() const { return street_; }
  int GetHouse() const { return house_; }
  int GetDistance() const { return distance_; }
  const std::string& GetEntrance() const { return entrance_; }

 private:
  std::string street_ = "Main";
  int house_ = 1;
  int distance_ = 3;
  std::string entrance_ = "A";
};

