#include "Console.h"
#include "Receipt.h"
#include "PurchaseLine.h"
#include "Delivery.h"
#include "DeliveryZone.h"
#include "RecipePart.h"
#include "Review.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace {
void PrintHelp() {
  std::cout << "menu | add COUNT | total | pay CASH | receipt | bake | pack | deliver\n"
            << "stock | restock GRAMS | consume GRAMS | review STARS TEXT | new | exit\n";
}

int ReadPositive(std::istringstream& args) {
  int value = 0;
  if (!(args >> value) || value <= 0) throw std::runtime_error("Expected positive number");
  return value;
}

void ReviewCommand(std::istringstream& args) {
  int stars = ReadPositive(args);
  std::string text;
  std::getline(args >> std::ws, text);
  Review review;
  review.Rate(stars);
  review.Write(text);
  review.Publish();
  std::cout << "Published: " << review.GetStars() << ' ' << review.GetText() << '\n';
}
}

void Console::Run() {
  shop_.OpenMenu(MenuItem{});
  PrintHelp();
  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream args(line);
    std::string command;
    args >> command;
    if (command == "exit") return;
    try {
      Execute(command, args);
    } catch (const std::exception& error) {
      std::cout << "Error: " << error.what() << '\n';
    }
  }
}

void Console::Execute(const std::string& command, std::istringstream& args) {
  if (command == "menu") std::cout << "Classic 600 cents\n";
  else if (command == "add") {
    order_.Add(OrderLine(MenuItem{}, ReadPositive(args)));
    std::cout << "Total: " << order_.Total() << " cents\n";
  } else if (command == "total") std::cout << order_.Total() << " cents\n";
  else if (command == "pay") Pay(args);
  else if (command == "receipt") std::cout << Receipt(order_, payment_).Text() << '\n';
  else if (command == "bake") Bake();
  else if (command == "pack") Pack();
  else if (command == "deliver") Deliver();
  else if (command == "stock" || command == "restock" || command == "consume") Stock(command, args);
  else if (command == "review") ReviewCommand(args);
  else if (command == "new") Reset();
  else PrintHelp();
}

void Console::Stock(const std::string& command, std::istringstream& args) {
  if (command == "stock") {
    for (const auto& item : stock_.GetItems()) {
      std::cout << item.GetIngredient().GetName() << ' ' << item.GetGrams() << " g\n";
    }
    return;
  }
  int grams = ReadPositive(args);
  if (command == "consume") stock_.Withdraw(Ingredient{}, grams);
  else {
    PurchaseLine line(Ingredient{}, Supplier{}, grams);
    line.Receive(grams);
    StockItem item;
    item.Receive(line);
    stock_.Store(item);
  }
}

void Console::Pay(std::istringstream& args) {
  int cash = ReadPositive(args);
  payment_ = shop_.Sell(order_, cash);
  std::cout << "Paid, change: " << payment_.GetChange() << '\n';
}

void Console::Bake() {
  if (!payment_.GetCaptured() || baked_) throw std::runtime_error("Pay before baking");
  int count = 0;
  for (const auto& line : order_.GetLines()) count += line.GetQuantity();
  RecipePart part;
  part.TakeFrom(stock_, count);
  for (int index = 0; index < count; ++index) shop_.Bake(BakingTask{});
  baked_ = true;
  std::cout << "Baked\n";
}

void Console::Pack() {
  if (!baked_ || packed_) throw std::runtime_error("Bake before packing");
  packaging_.Pack(order_);
  packed_ = true;
  std::cout << "Packed\n";
}

void Console::Deliver() {
  if (!packed_) throw std::runtime_error("Pack before delivery");
  Delivery delivery;
  delivery.Accept(order_, Address{});
  delivery.Dispatch(courier_, DeliveryZone{});
  delivery.Complete(courier_);
  packed_ = false;
  std::cout << "Delivered\n";
}

void Console::Reset() {
  order_ = Order{};
  payment_ = Payment{};
  baked_ = false;
  packed_ = false;
}
