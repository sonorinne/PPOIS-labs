#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "Ingredient.h"
#include "Supplier.h"
#include "PurchaseLine.h"
#include "PurchaseOrder.h"
#include "StockItem.h"
#include "StockRoom.h"
#include "RecipePart.h"
#include "Recipe.h"
#include "PizzaSize.h"
#include "Dough.h"
#include "Sauce.h"
#include "Topping.h"
#include "Pizza.h"
#include "MenuItem.h"
#include "Menu.h"
#include "Address.h"
#include "Customer.h"
#include "LoyaltyAccount.h"
#include "Coupon.h"
#include "OrderLine.h"
#include "Order.h"
#include "Payment.h"
#include "CashRegister.h"
#include "Oven.h"
#include "BakingTask.h"
#include "Cook.h"
#include "Kitchen.h"
#include "PizzaBox.h"
#include "Packaging.h"
#include "Courier.h"
#include "DeliveryZone.h"
#include "Delivery.h"
#include "PickupSlot.h"
#include "Table.h"
#include "Reservation.h"
#include "Review.h"
#include "WorkShift.h"
#include "Pizzeria.h"
#include "InvalidAmount.h"
#include "InvalidQuantity.h"
#include "StockShortage.h"
#include "InactiveSupplier.h"
#include "EmptyRecipe.h"
#include "UnavailableItem.h"
#include "InvalidAddress.h"
#include "InvalidOrder.h"
#include "InsufficientPayment.h"
#include "UnavailableOven.h"
#include "UnavailableCourier.h"
#include "InvalidReservation.h"

TEST_CASE("Ingredient domain operations") {
  Ingredient item;
  CHECK(item.GetName() == "flour");
  CHECK(item.GetCalories() == 350);
  CHECK(item.GetPrice() == 100);
  CHECK(item.GetAllergen() == true);
  CHECK(item.Cost(1000) == 100);
  CHECK(item.Energy(100) == 350);
  CHECK_FALSE(item.Allowed(true));
  CHECK(item.Allowed(false));
  CHECK_THROWS_AS(item.Cost(0), InvalidQuantity);
  CHECK_THROWS_AS(item.Energy(0), InvalidQuantity);
  Ingredient cheese("cheese",300,200,false);
  CHECK(cheese.Allowed(true));
  CHECK(cheese.Cost(100)==20);
}

TEST_CASE("Supplier domain operations") {
  Supplier item;
  CHECK(item.GetName() == "Farm");
  CHECK(item.GetActive() == true);
  CHECK(item.GetMinimum() == 100);
  CHECK(item.GetShipping() == 50);
  Ingredient ingredient;
  CHECK(item.Quote(ingredient,100) == 60);
  CHECK(item.Quote(ingredient,1000) == 100);
  item.Suspend();
  CHECK_THROWS_AS(item.Quote(ingredient,100),InactiveSupplier);
  CHECK_THROWS_AS(item.Suspend(),InactiveSupplier);
  item.Resume();
  CHECK(item.GetActive());
  Supplier farm("Farm2",100,50);
  CHECK(farm.GetName()=="Farm2");
}

TEST_CASE("PurchaseLine domain operations") {
  PurchaseLine item;
  CHECK(item.GetGrams() == 1000);
  CHECK(item.GetReceived() == 0);
  CHECK(item.Total() == 100);
  item.Receive(400);
  CHECK(item.Outstanding() == 600);
  CHECK_THROWS_AS(item.Receive(0),InvalidQuantity);
  CHECK_THROWS_AS(item.Receive(1000),InvalidQuantity);

}

TEST_CASE("PurchaseOrder domain operations") {
  PurchaseOrder item;
  CHECK(item.GetLines().empty());
  CHECK(item.GetClosed() == false);
  CHECK(item.GetPaid() == 0);
  CHECK_THROWS_AS(item.Close(100),InvalidOrder);
  PurchaseLine line;
  item.Add(line);
  CHECK(item.Total()==100);
  CHECK_THROWS_AS(item.Close(0),InsufficientPayment);
  item.Close(100);
  CHECK(item.GetPaid()==100);
  CHECK_THROWS_AS(item.Add(line),InvalidOrder);
  CHECK_THROWS_AS(item.Close(100),InvalidOrder);

}

TEST_CASE("StockItem domain operations") {
  StockItem item;
  CHECK(item.GetGrams() == 0);
  CHECK(item.GetMinimum() == 500);
  CHECK(item.GetWasted() == 0);
  PurchaseLine line;
  CHECK_THROWS_AS(item.Receive(line),InvalidQuantity);
  line.Receive(1000);
  item.Receive(line);
  CHECK_THROWS_AS(item.Consume(0),InvalidQuantity);
  CHECK_THROWS_AS(item.Consume(1001),StockShortage);
  item.Consume(200);
  item.Discard(100);
  CHECK(item.GetGrams()==700);
  CHECK(item.GetWasted()==100);
  Ingredient cheese("cheese",300,200,false);
  PurchaseLine wrong(cheese,Supplier{},100);
  wrong.Receive(100);
  CHECK_THROWS_AS(item.Receive(wrong),UnavailableItem);
}

TEST_CASE("StockRoom domain operations") {
  StockRoom item;
  CHECK(item.GetItems().empty());
  CHECK(item.GetCapacity() == 50);
  CHECK(item.GetDeliveries() == 0);
  CHECK(item.GetWithdrawals() == 0);
  Ingredient ingredient;
  CHECK_THROWS_AS(item.Withdraw(ingredient,1),UnavailableItem);
  StockItem stock;
  PurchaseLine line;
  line.Receive(1000);
  stock.Receive(line);
  item.Store(stock);
  item.Store(stock);
  CHECK(item.CountLow()==0);
  item.Withdraw(ingredient,1600);
  CHECK(item.CountLow()==1);
  for(int index=1;index<50;++index) item.Store(StockItem(Ingredient(std::to_string(index),1,1,false)));
  CHECK_THROWS_AS(item.Store(StockItem(Ingredient("extra",1,1,false))),StockShortage);

}

TEST_CASE("RecipePart domain operations") {
  RecipePart item;
  CHECK(item.GetGrams() == 200);
  CHECK(item.GetLossPercent() == 5);
  CHECK(item.GetStage() == "dough");
  CHECK(item.Required(2)==420);
  CHECK(item.Cost(1)==21);
  CHECK_THROWS_AS(item.Required(0),InvalidQuantity);
  StockRoom room;
  StockItem stock;
  PurchaseLine line;
  line.Receive(1000);
  stock.Receive(line);
  room.Store(stock);
  item.TakeFrom(room,1);
  CHECK(room.GetWithdrawals()==1);
  RecipePart cheese(Ingredient("cheese",300,200,false),50);
  CHECK(cheese.Cost(1)==10);
}

TEST_CASE("Recipe domain operations") {
  Recipe item;
  CHECK(item.GetName() == "Classic");
  CHECK(item.GetParts().empty());
  CHECK(item.GetBakeMinutes() == 8);
  CHECK(item.GetPortions() == 1);
  CHECK_THROWS_AS(item.Cost(),EmptyRecipe);
  CHECK_THROWS_AS(item.RequiredGrams(),EmptyRecipe);
  item.Add(RecipePart{});
  CHECK(item.Cost()==21);
  CHECK(item.RequiredGrams()==210);

}

TEST_CASE("PizzaSize domain operations") {
  PizzaSize item;
  CHECK(item.GetName() == "medium");
  CHECK(item.GetDiameter() == 30);
  CHECK(item.GetSlices() == 8);
  CHECK(item.GetPricePercent() == 100);
  CHECK(item.ScalePrice(500)==500);
  CHECK_THROWS_AS(item.ScalePrice(-1),InvalidAmount);
  CHECK(item.Fits(30));
  CHECK_FALSE(item.Fits(20));
  CHECK(item.SliceWeight(800)==100);
  CHECK_THROWS_AS(item.SliceWeight(0),InvalidQuantity);
  PizzaSize large("large",40,8,120);
  CHECK(large.ScalePrice(100)==120);
}

TEST_CASE("Dough domain operations") {
  Dough item;
  CHECK(item.GetGrams() == 300);
  CHECK(item.GetRestedMinutes() == 0);
  CHECK(item.GetRequiredMinutes() == 30);
  CHECK_FALSE(item.Ready());
  CHECK_THROWS_AS(item.Use(1),StockShortage);
  CHECK_THROWS_AS(item.Rest(0),InvalidQuantity);
  CHECK_THROWS_AS(item.Use(0),InvalidQuantity);
  item.Rest(30);
  CHECK(item.Ready());
  CHECK(item.Use(100)==10);

}

TEST_CASE("Sauce domain operations") {
  Sauce item;
  CHECK(item.GetGrams() == 500);
  CHECK(item.GetServing() == 50);
  CHECK(item.GetSpicy() == false);
  CHECK(item.Portions()==10);
  CHECK_THROWS_AS(item.Pour(0),InvalidQuantity);
  CHECK_THROWS_AS(item.Pour(11),StockShortage);
  item.Pour(2);
  CHECK(item.Portions()==8);
  Customer customer;
  CHECK(item.Suitable(customer));
  Customer sensitive;
  sensitive.RequireAllergenFree();
  CHECK(item.Suitable(sensitive));
}

TEST_CASE("Topping domain operations") {
  Topping item;
  CHECK(item.GetGrams() == 30);
  CHECK(item.GetSurcharge() == 80);
  CHECK(item.GetAvailable() == true);
  CHECK(item.Cost(2)==178);
  CHECK_THROWS_AS(item.Cost(0),InvalidQuantity);
  Customer customer;
  CHECK(item.CanServe(customer));
  item.StopSales();
  CHECK_FALSE(item.CanServe(customer));
  CHECK_THROWS_AS(item.Cost(1),UnavailableItem);

}

TEST_CASE("Pizza domain operations") {
  Pizza item;
  CHECK(item.GetToppings().empty());
  CHECK(item.GetBasePrice() == 600);
  CHECK(item.Price()==600);
  item.AddTopping(Topping{});
  CHECK(item.Price()==689);
  CHECK(item.Margin()==668);
  Pizza empty(Recipe{}, PizzaSize{}, 600);
  CHECK_THROWS_AS(empty.Margin(),EmptyRecipe);
  Recipe recipe;
  recipe.Add(RecipePart{});
  Pizza complete(recipe,PizzaSize{},600);
  CHECK(complete.Margin()==579);
}

TEST_CASE("MenuItem domain operations") {
  MenuItem item;
  CHECK(item.GetName() == "Classic");
  CHECK(item.GetAvailable() == true);
  CHECK(item.GetSold() == 0);
  CHECK(item.Quote(2)==1200);
  CHECK_THROWS_AS(item.Quote(0),InvalidQuantity);
  item.Sell(2);
  CHECK(item.GetSold()==2);
  item.StopSales();
  CHECK_THROWS_AS(item.Quote(1),UnavailableItem);
  MenuItem named(Pizza{},"Margherita");
  CHECK(named.GetName()=="Margherita");
}

TEST_CASE("Menu domain operations") {
  Menu item;
  CHECK(item.GetItems().empty());
  CHECK(item.GetRevision() == 0);
  CHECK(item.GetOpen() == true);
  CHECK(item.GetTitle() == "Pizzeria");
  CHECK_THROWS_AS(item.Find("absent"),UnavailableItem);
  item.Add(MenuItem{});
  CHECK(item.Find("Classic").Quote(1)==600);
  item.Close();
  CHECK_THROWS_AS(item.Add(MenuItem{}),UnavailableItem);

}

TEST_CASE("Address domain operations") {
  Address item;
  CHECK(item.GetStreet() == "Main");
  CHECK(item.GetHouse() == 1);
  CHECK(item.GetDistance() == 3);
  CHECK(item.GetEntrance() == "A");
  item.Validate();
  CHECK(item.InRange(3));
  CHECK_FALSE(item.InRange(2));
  CHECK(item.Label()=="Main 1 / A");
  Address bad("",0,-1,"");
  CHECK_THROWS_AS(bad.Validate(),InvalidAddress);
}

TEST_CASE("Customer domain operations") {
  Customer item;
  CHECK(item.GetName() == "Guest");
  CHECK(item.GetAvoidAllergens() == false);
  CHECK(item.GetOrders() == 0);
  item.ChooseAddress(Address{});
  item.RequireAllergenFree();
  CHECK(item.GetAvoidAllergens());
  Order order;
  CHECK_THROWS_AS(item.RecordOrder(order),InvalidOrder);
  order.Add(OrderLine{});
  item.RecordOrder(order);
  CHECK(item.GetOrders()==1);
  Customer named("Anna",Address{});
  CHECK(named.GetName()=="Anna");
}

TEST_CASE("LoyaltyAccount domain operations") {
  LoyaltyAccount item;
  CHECK(item.GetPoints() == 0);
  CHECK(item.GetEarned() == 0);
  CHECK(item.GetSpent() == 0);
  Payment payment;
  CHECK_THROWS_AS(item.Earn(payment),InsufficientPayment);
  Order order;
  order.Add(OrderLine{});
  payment.Capture(order,600);
  item.Earn(payment);
  CHECK(item.GetPoints()==6);
  CHECK_THROWS_AS(item.Redeem(0),InvalidAmount);
  CHECK_THROWS_AS(item.Redeem(7),InsufficientPayment);
  CHECK_THROWS_AS(item.TransferTo(item,1),InvalidAmount);
  LoyaltyAccount target;
  item.TransferTo(target,2);
  CHECK(target.GetPoints()==2);
  CHECK(item.Redeem(4)==4);

}

TEST_CASE("Coupon domain operations") {
  Coupon item;
  CHECK(item.GetCode() == "WELCOME");
  CHECK(item.GetPercent() == 10);
  CHECK(item.GetMinimum() == 500);
  CHECK(item.GetUsed() == false);
  Order order;
  CHECK_THROWS_AS(item.Discount(order),InvalidOrder);
  order.Add(OrderLine{});
  Customer customer;
  CHECK(item.Eligible(customer));
  CHECK(item.Discount(order)==60);
  item.Redeem(order);
  CHECK(order.Total()==540);
  CHECK_FALSE(item.Eligible(customer));
  CHECK_THROWS_AS(item.Discount(order),InvalidOrder);

}

TEST_CASE("OrderLine domain operations") {
  OrderLine item;
  CHECK(item.GetQuantity() == 1);
  CHECK(item.GetComment() == "");
  CHECK(item.GetPacked() == false);
  CHECK(item.Total()==600);
  CHECK_THROWS_AS(item.Increase(0),InvalidQuantity);
  item.Increase(1);
  CHECK(item.Total()==1200);
  item.Pack(PizzaBox{});
  CHECK_THROWS_AS(item.Pack(PizzaBox{}),InvalidOrder);
  CHECK_THROWS_AS(item.Increase(1),InvalidQuantity);
  OrderLine pair(MenuItem{},2);
  CHECK(pair.Total()==1200);
}

TEST_CASE("Order domain operations") {
  Order item;
  CHECK(item.GetLines().empty());
  CHECK(item.GetDiscount() == 0);
  CHECK(item.GetConfirmed() == false);
  CHECK(item.GetCancelled() == false);
  CHECK_THROWS_AS(item.Confirm(),InvalidOrder);
  CHECK_THROWS_AS(item.ApplyDiscount(-1),InvalidOrder);
  item.Add(OrderLine{});
  CHECK(item.Subtotal()==600);
  item.ApplyDiscount(50);
  CHECK(item.Total()==550);
  item.Confirm();
  CHECK_THROWS_AS(item.Confirm(),InvalidOrder);
  CHECK_THROWS_AS(item.Add(OrderLine{}),InvalidOrder);
  item.Cancel();
  CHECK_THROWS_AS(item.Cancel(),InvalidOrder);

}

TEST_CASE("Payment domain operations") {
  Payment item;
  CHECK(item.GetAmount() == 0);
  CHECK(item.GetChange() == 0);
  CHECK(item.GetCaptured() == false);
  CHECK(item.GetRefunded() == false);
  CHECK(item.GetRegistered() == false);
  Order order;
  CHECK_THROWS_AS(item.Capture(order,100),InvalidOrder);
  CHECK_THROWS_AS(item.Refund(),InvalidOrder);
  order.Add(OrderLine{});
  CHECK_THROWS_AS(item.Capture(order,0),InsufficientPayment);
  item.Capture(order,700);
  CHECK(item.GetChange()==100);
  CHECK(item.Net()==600);
  CHECK_THROWS_AS(item.Capture(order,700),InvalidOrder);
  CHECK(item.Refund()==600);
  CHECK(item.Net()==0);
  CHECK_THROWS_AS(item.Refund(),InvalidOrder);

}

TEST_CASE("CashRegister domain operations") {
  CashRegister item;
  CHECK(item.GetBalance() == 0);
  CHECK(item.GetRevenue() == 0);
  CHECK(item.GetRefunds() == 0);
  CHECK(item.GetOpen() == true);
  Payment payment;
  CHECK_THROWS_AS(item.Accept(payment),InvalidOrder);
  Order order;
  order.Add(OrderLine{});
  payment.Capture(order,600);
  CHECK_THROWS_AS(item.Refund(payment),InsufficientPayment);
  item.Accept(payment);
  CHECK_THROWS_AS(item.Accept(payment),InvalidOrder);
  item.Refund(payment);
  CHECK(item.GetRefunds()==600);
  CHECK(item.Close()==0);
  CHECK_THROWS_AS(item.Close(),InvalidOrder);
  CHECK_THROWS_AS(item.Accept(payment),InvalidOrder);
  CHECK_THROWS_AS(item.Refund(payment),InvalidOrder);

}

TEST_CASE("Oven domain operations") {
  Oven item;
  CHECK(item.GetTemperature() == 20);
  CHECK(item.GetRequiredTemperature() == 250);
  CHECK(item.GetDiameter() == 40);
  CHECK(item.GetOccupied() == false);
  Pizza pizza;
  CHECK_THROWS_AS(item.Load(pizza),UnavailableOven);
  CHECK_THROWS_AS(item.Heat(0),InvalidQuantity);
  CHECK_THROWS_AS(item.Unload(),UnavailableOven);
  item.Heat(230);
  item.Load(pizza);
  CHECK_THROWS_AS(item.Load(pizza),UnavailableOven);
  item.Unload();
  CHECK_FALSE(item.GetOccupied());

}

TEST_CASE("BakingTask domain operations") {
  BakingTask item;
  CHECK(item.GetElapsed() == 0);
  CHECK(item.GetRequired() == 8);
  CHECK(item.GetStarted() == false);
  CHECK_FALSE(item.Ready());
  CHECK_THROWS_AS(item.Advance(1),InvalidQuantity);
  Oven oven;
  oven.Heat(230);
  item.Start(oven);
  CHECK_THROWS_AS(item.Start(oven),InvalidOrder);
  item.Advance(8);
  CHECK(item.Ready());

}

TEST_CASE("Cook domain operations") {
  Cook item;
  CHECK(item.GetName() == "Alex");
  CHECK(item.GetOnShift() == true);
  CHECK(item.GetPrepared() == 0);
  CHECK(item.GetMinutesWorked() == 0);
  Recipe recipe;
  recipe.Add(RecipePart{});
  item.Prepare(recipe);
  CHECK(item.GetPrepared()==1);
  Oven oven;
  oven.Heat(230);
  BakingTask task;
  CHECK_THROWS_AS(item.Finish(task,oven),InvalidOrder);
  task.Start(oven);
  task.Advance(8);
  item.Finish(task,oven);
  item.EndShift();
  CHECK_THROWS_AS(item.Prepare(recipe),InvalidOrder);

}

TEST_CASE("Kitchen domain operations") {
  Kitchen item;
  CHECK(item.GetQueue().empty());
  CHECK(item.GetCompleted() == 0);
  CHECK_THROWS_AS(item.BakeNext(),InvalidOrder);
  item.WarmUp();
  item.Enqueue(BakingTask{});
  item.BakeNext();
  CHECK(item.GetCompleted()==1);
  CHECK(item.GetQueue().empty());

}

TEST_CASE("PizzaBox domain operations") {
  PizzaBox item;
  CHECK(item.GetDiameter() == 35);
  CHECK(item.GetAvailable() == 20);
  CHECK(item.GetCost() == 30);
  CHECK(item.GetRecyclable() == true);
  CHECK(item.Fits(Pizza{}));
  CHECK(item.Take(2)==60);
  CHECK_THROWS_AS(item.Take(0),InvalidQuantity);
  CHECK_THROWS_AS(item.Take(21),StockShortage);
  CHECK_THROWS_AS(item.Restock(0),InvalidQuantity);
  item.Restock(2);
  CHECK(item.GetAvailable()==20);

}

TEST_CASE("Packaging domain operations") {
  Packaging item;
  CHECK(item.GetNapkins() == 100);
  CHECK(item.GetPackedOrders() == 0);
  CHECK(item.GetUsedBoxes() == 0);
  Order order;
  CHECK_THROWS_AS(item.Pack(order),StockShortage);
  order.Add(OrderLine{});
  CHECK(item.RequiredBoxes(order)==1);
  item.Pack(order);
  CHECK(item.GetUsedBoxes()==1);
  CHECK_THROWS_AS(item.RefillNapkins(0),InvalidQuantity);
  item.RefillNapkins(1);
  CHECK(item.GetNapkins()==100);

}

TEST_CASE("Courier domain operations") {
  Courier item;
  CHECK(item.GetName() == "Sam");
  CHECK(item.GetBusy() == false);
  CHECK(item.GetDistance() == 0);
  CHECK(item.GetDeliveries() == 0);
  Address address;
  CHECK(item.Estimate(address)==25);
  CHECK_THROWS_AS(item.Complete(address),UnavailableCourier);
  item.Assign(address);
  CHECK_THROWS_AS(item.Assign(address),UnavailableCourier);
  item.Complete(address);
  CHECK(item.GetDistance()==3);

}

TEST_CASE("DeliveryZone domain operations") {
  DeliveryZone item;
  CHECK(item.GetName() == "City");
  CHECK(item.GetMaximum() == 10);
  CHECK(item.GetPerKm() == 20);
  CHECK(item.GetFreeFrom() == 2000);
  Address address;
  Order order;
  CHECK(item.Covers(address));
  CHECK(item.Fee(address,order)==60);
  CHECK(item.Remaining(address)==7);
  OrderLine line;
  line.Increase(3);
  order.Add(line);
  CHECK(item.Fee(address,order)==0);
  Address distant("Far",1,20,"A");
  CHECK_FALSE(item.Covers(distant));
  CHECK_THROWS_AS(item.Fee(distant,order),InvalidAddress);
  CHECK_THROWS_AS(item.Remaining(distant),InvalidAddress);
}

TEST_CASE("Delivery domain operations") {
  Delivery item;
  CHECK(item.GetDispatched() == false);
  CHECK(item.GetDelivered() == false);
  Order order;
  Address address;
  Courier courier;
  DeliveryZone zone;
  CHECK_THROWS_AS(item.Accept(order,address),InvalidOrder);
  CHECK_THROWS_AS(item.Dispatch(courier,zone),InvalidOrder);
  CHECK_THROWS_AS(item.Complete(courier),InvalidOrder);
  order.Add(OrderLine{});
  order.Confirm();
  item.Accept(order,address);
  item.Dispatch(courier,zone);
  CHECK_THROWS_AS(item.Dispatch(courier,zone),InvalidOrder);
  CHECK_THROWS_AS(item.Accept(order,address),InvalidOrder);
  item.Complete(courier);
  CHECK(item.GetDelivered());
  CHECK_THROWS_AS(item.Complete(courier),InvalidOrder);

}

TEST_CASE("PickupSlot domain operations") {
  PickupSlot item;
  CHECK(item.GetStart() == 600);
  CHECK(item.GetEnd() == 630);
  CHECK(item.GetCapacity() == 5);
  CHECK(item.GetReserved() == 0);
  CHECK(item.Contains(600));
  CHECK_FALSE(item.Contains(630));
  CHECK_THROWS_AS(item.Release(),InvalidReservation);
  Order order;
  CHECK_THROWS_AS(item.Reserve(order),InvalidReservation);
  order.Add(OrderLine{});
  order.Confirm();
  for(int i=0;i<5;++i)item.Reserve(order);
  CHECK_THROWS_AS(item.Reserve(order),InvalidReservation);
  item.Release();
  CHECK(item.GetReserved()==4);

}

TEST_CASE("Table domain operations") {
  Table item;
  CHECK(item.GetNumber() == 1);
  CHECK(item.GetSeats() == 4);
  CHECK(item.GetGuests() == 0);
  CHECK(item.GetClean() == true);
  CHECK_THROWS_AS(item.Vacate(),InvalidReservation);
  CHECK_THROWS_AS(item.Seat(0),InvalidReservation);
  item.Seat(2);
  CHECK_THROWS_AS(item.Clean(),InvalidReservation);
  CHECK_THROWS_AS(item.Seat(1),InvalidReservation);
  item.Vacate();
  CHECK_THROWS_AS(item.Seat(1),InvalidReservation);
  item.Clean();
  CHECK(item.GetClean());

}

TEST_CASE("Reservation domain operations") {
  Reservation item;
  CHECK(item.GetGuests() == 2);
  CHECK(item.GetMinute() == 600);
  CHECK(item.GetActive() == true);
  CHECK_THROWS_AS(item.Postpone(0),InvalidReservation);
  item.Postpone(30);
  CHECK(item.GetMinute()==630);
  Table table;
  item.CheckIn(table);
  CHECK_THROWS_AS(item.CheckIn(table),InvalidReservation);
  CHECK_THROWS_AS(item.Cancel(),InvalidReservation);
  Reservation other;
  other.Cancel();
  CHECK_FALSE(other.GetActive());

}

TEST_CASE("Review domain operations") {
  Review item;
  CHECK(item.GetStars() == 5);
  CHECK(item.GetText() == "");
  CHECK(item.GetPublished() == false);
  CHECK_THROWS_AS(item.Publish(),InvalidOrder);
  CHECK_THROWS_AS(item.Rate(0),InvalidQuantity);
  CHECK_THROWS_AS(item.Write(""),InvalidOrder);
  item.Rate(4);
  item.Write("Good pizza");
  item.Publish();
  CHECK(item.GetPublished());
  CHECK_THROWS_AS(item.Rate(5),InvalidQuantity);
  CHECK_THROWS_AS(item.Write("x"),InvalidOrder);
  CHECK_THROWS_AS(item.Publish(),InvalidOrder);

}

TEST_CASE("WorkShift domain operations") {
  WorkShift item;
  CHECK(item.GetStart() == 600);
  CHECK(item.GetEnd() == 0);
  CHECK(item.GetRate() == 500);
  CHECK_THROWS_AS(item.Duration(),InvalidOrder);
  CHECK_THROWS_AS(item.Finish(500),InvalidQuantity);
  item.Finish(720);
  CHECK(item.Duration()==120);
  CHECK(item.Salary()==1000);
  CHECK_THROWS_AS(item.Finish(800),InvalidQuantity);

}

TEST_CASE("Pizzeria domain operations") {
  Pizzeria item;
  CHECK(item.GetServed() == 0);
  Order order;
  CHECK_THROWS_AS(item.Sell(order,100),InvalidOrder);
  item.OpenMenu(MenuItem{});
  order.Add(OrderLine{});
  Payment payment = item.Sell(order,600);
  CHECK(payment.Net()==600);
  item.Bake(BakingTask{});
  CHECK(item.GetServed()==1);
  CHECK(item.GetKitchen().GetCompleted()==1);

}

TEST_CASE("Constructors reject invalid domain data") {
  CHECK_THROWS_AS(Ingredient("", 1, 1, false), InvalidAmount);
  CHECK_THROWS_AS(Ingredient("flour", -1, 1, false), InvalidAmount);
  CHECK_THROWS_AS(Ingredient("flour", 1, -1, false), InvalidAmount);
  CHECK_THROWS_AS(Supplier("", 1, 1), InvalidAmount);
  CHECK_THROWS_AS(Supplier("farm", -1, 1), InvalidAmount);
  CHECK_THROWS_AS(Supplier("farm", 1, -1), InvalidAmount);
  CHECK_THROWS_AS(PizzaSize("medium", 0, 8, 100), InvalidQuantity);
  CHECK_THROWS_AS(PizzaSize("medium", 30, 0, 100), InvalidQuantity);
  CHECK_THROWS_AS(PizzaSize("medium", 30, 8, 0), InvalidQuantity);
  CHECK_THROWS_AS(RecipePart(Ingredient{}, 0), InvalidQuantity);
}
