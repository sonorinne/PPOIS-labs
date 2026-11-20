#pragma once
#include "Pizzeria.h"
#include "Order.h"
#include "Payment.h"
#include "StockRoom.h"
#include "Packaging.h"
#include "Courier.h"
#include <iosfwd>
#include <string>

/// Console commands for the pizzeria application.
class Console {
 public:
  void Run();

 private:
  void Execute(const std::string& command, std::istringstream& args);
  void Stock(const std::string& command, std::istringstream& args);
  void Pay(std::istringstream& args);
  void Bake();
  void Pack();
  void Deliver();
  void Reset();
  Pizzeria shop_;
  Order order_;
  Payment payment_;
  StockRoom stock_;
  Packaging packaging_;
  Courier courier_;
  bool baked_ = false;
  bool packed_ = false;
};
