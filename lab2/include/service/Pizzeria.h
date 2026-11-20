#pragma once
#include <string>
#include <vector>
#include "Menu.h"
#include "CashRegister.h"
#include "Kitchen.h"
class MenuItem;
class Order;
class Payment;
class BakingTask;

/// Продажа и приготовление в пиццерии.
class Pizzeria {
 public:
  void OpenMenu(const MenuItem& item);
  Payment Sell(Order& order, int tendered);
  void Bake(const BakingTask& task);
  const Menu& GetMenu() const { return menu_; }
  const CashRegister& GetCash() const { return cash_; }
  const Kitchen& GetKitchen() const { return kitchen_; }
  int GetServed() const { return served_; }

 private:
  Menu menu_;
  CashRegister cash_;
  Kitchen kitchen_;
  int served_ = 0;
};
