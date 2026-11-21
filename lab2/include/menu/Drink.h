#pragma once
#include <string>
#include <vector>

class InvalidQuantity;

/// Напиток и запас порций.
class Drink {
 public:
  bool CanSell(int count) const;
  int Sell(int count);
  void Restock(int count);
  const std::string& GetName() const { return name_; }
  int GetPrice() const { return price_; }
  int GetMilliliters() const { return milliliters_; }
  int GetAvailable() const { return available_; }
 private:
  std::string name_ = "Juice";
  int price_ = 200;
  int milliliters_ = 330;
  int available_ = 10;
};
