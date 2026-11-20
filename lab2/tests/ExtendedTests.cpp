#include <doctest/doctest.h>
#include "Ingredient.h"
#include "PurchaseLine.h"
#include "PurchaseOrder.h"
#include "StockItem.h"
#include "StockRoom.h"
#include "Supplier.h"
#include "Dough.h"
#include "Menu.h"
#include "MenuItem.h"
#include "Pizza.h"
#include "PizzaSize.h"
#include "Recipe.h"
#include "RecipePart.h"
#include "Sauce.h"
#include "Topping.h"
#include "Address.h"
#include "CashRegister.h"
#include "Coupon.h"
#include "Customer.h"
#include "LoyaltyAccount.h"
#include "Order.h"
#include "OrderLine.h"
#include "Payment.h"
#include "BakingTask.h"
#include "Cook.h"
#include "Kitchen.h"
#include "Oven.h"
#include "Packaging.h"
#include "PizzaBox.h"
#include "Courier.h"
#include "Delivery.h"
#include "DeliveryZone.h"
#include "PickupSlot.h"
#include "Pizzeria.h"
#include "Reservation.h"
#include "Review.h"
#include "Table.h"
#include "WorkShift.h"
#include "EmptyRecipe.h"
#include "InactiveSupplier.h"
#include "InsufficientPayment.h"
#include "InvalidAddress.h"
#include "InvalidAmount.h"
#include "InvalidOrder.h"
#include "InvalidQuantity.h"
#include "InvalidReservation.h"
#include "StockShortage.h"
#include "UnavailableCourier.h"
#include "UnavailableItem.h"
#include "UnavailableOven.h"
#include "Drink.h"
#include "MealDeal.h"
#include "LunchOffer.h"
#include "WasteRecord.h"
#include "StockAudit.h"
#include "SupplierInvoice.h"
#include "Receipt.h"
#include "RefundRequest.h"
#include "ExpenseBook.h"
#include "ThermalBag.h"
#include "DeliveryRoute.h"
#include "SalesReport.h"

TEST_CASE("Drink operations") {
  Drink item;
  CHECK(item.GetName()=="Juice");
  CHECK(item.GetMilliliters()==330);
  CHECK(item.GetPrice()==200);
  CHECK(item.CanSell(10));
  CHECK_FALSE(item.CanSell(0));
  CHECK_FALSE(item.CanSell(11));
  CHECK_THROWS_AS(item.Sell(0),InvalidQuantity);
  CHECK(item.Sell(2)==400);
  CHECK(item.GetAvailable()==8);
  CHECK_THROWS_AS(item.Restock(0),InvalidQuantity);
  item.Restock(2);
  CHECK(item.GetAvailable()==10);
}

TEST_CASE("MealDeal operations") {
  MealDeal item;
  CHECK(item.Price()==700);
  CHECK(item.CanServe(1));
  CHECK_THROWS_AS(item.Sell(11),UnavailableItem);
  CHECK(item.Sell(2)==1400);
  CHECK_FALSE(item.CanServe(9));
}

TEST_CASE("LunchOffer operations") {
  LunchOffer item;
  CHECK(item.GetStart()==720);
  CHECK(item.GetEnd()==900);
  CHECK(item.GetPercent()==15);
  CHECK(item.IsActive(720));
  CHECK_FALSE(item.IsActive(719));
  CHECK_FALSE(item.IsActive(900));
  CHECK(item.Discount(2)==180);
  CHECK(item.Quote(800,1)==510);
  CHECK_THROWS_AS(item.Quote(0,1),UnavailableItem);
}

TEST_CASE("WasteRecord operations") {
  WasteRecord item;
  CHECK(item.GetGrams()==100);
  CHECK(item.GetReason()=="expired");
  CHECK_FALSE(item.GetBooked());
  CHECK(item.Cost()==10);
  CHECK(item.Describe()=="flour: 100 g, expired");
  StockRoom stock;
  CHECK_THROWS_AS(item.Apply(stock),UnavailableItem);
  CHECK_FALSE(item.GetBooked());
  PurchaseLine line;
  line.Receive(1000);
  StockItem flour;
  flour.Receive(line);
  stock.Store(flour);
  item.Apply(stock);
  CHECK(item.GetBooked());
  CHECK_THROWS_AS(item.Apply(stock),InvalidOrder);
}

TEST_CASE("StockAudit operations") {
  StockAudit item;
  CHECK_FALSE(item.GetCaptured());
  CHECK_THROWS_AS(item.TotalGrams(),InvalidOrder);
  StockRoom stock;
  PurchaseLine line;
  line.Receive(1000);
  StockItem flour;
  flour.Receive(line);
  stock.Store(flour);
  item.Capture(stock);
  CHECK(item.GetCaptured());
  CHECK(item.TotalGrams()==1000);
  stock.Withdraw(Ingredient{},100);
  CHECK(item.Difference(stock)==100);
}

TEST_CASE("SupplierInvoice operations") {
  SupplierInvoice item;
  CHECK(item.GetPaid()==0);
  CHECK_FALSE(item.GetSettled());
  CHECK_THROWS_AS(item.Outstanding(),InvalidOrder);
  PurchaseOrder purchase;
  CHECK_THROWS_AS(item.Issue(purchase),InvalidOrder);
  purchase.Add(PurchaseLine{});
  purchase.Close(100);
  item.Issue(purchase);
  CHECK(item.Outstanding()==100);
  CHECK_THROWS_AS(item.Settle(99),InsufficientPayment);
  item.Settle(100);
  CHECK(item.Outstanding()==0);
  CHECK(item.GetPaid()==100);
  CHECK(item.GetSettled());
  CHECK_THROWS_AS(item.Settle(100),InvalidOrder);
  CHECK_THROWS_AS(item.Issue(purchase),InvalidOrder);
}

TEST_CASE("Receipt operations") {
  Order order;
  order.Add(OrderLine{});
  Payment payment;
  payment.Capture(order,600);
  Receipt item(order,payment);
  Receipt empty;
  CHECK_THROWS_AS(empty.Total(),InvalidOrder);
  CHECK(item.GetShop()=="Pizzeria");
  CHECK(item.Total()==600);
  CHECK(item.Text()=="Pizzeria, total: 600");
  Order changed=order;
  changed.Add(OrderLine{});
  Receipt mismatch(changed,payment);
  CHECK_THROWS_AS(mismatch.Validate(),InvalidAmount);
}

TEST_CASE("RefundRequest operations") {
  Order order;
  order.Add(OrderLine{});
  Payment payment;
  payment.Capture(order,600);
  RefundRequest item(payment,"cancelled");
  CHECK(item.GetReason()=="cancelled");
  CHECK_FALSE(item.GetResolved());
  CHECK(item.RequestedAmount()==600);
  CashRegister cash;
  cash.Accept(payment);
  item.Resolve(cash);
  CHECK(item.GetResolved());
  CHECK(payment.GetRefunded());
  CHECK_THROWS_AS(item.Resolve(cash),InvalidOrder);
  RefundRequest bad(payment,"");
  CHECK_THROWS_AS(bad.Validate(),InvalidOrder);
}

TEST_CASE("ExpenseBook operations") {
  ExpenseBook item;
  CHECK(item.GetPurchases()==0);
  CHECK(item.GetWages()==0);
  CHECK(item.GetWaste()==0);
  PurchaseOrder purchase;
  CHECK_THROWS_AS(item.RecordPurchase(purchase),InvalidOrder);
  purchase.Add(PurchaseLine{});
  purchase.Close(100);
  item.RecordPurchase(purchase);
  WorkShift shift;
  shift.Finish(660);
  item.RecordShift(shift);
  WasteRecord waste;
  CHECK_THROWS_AS(item.RecordWaste(waste),InvalidOrder);
  StockRoom stock;
  PurchaseLine line;
  line.Receive(1000);
  StockItem flour;
  flour.Receive(line);
  stock.Store(flour);
  waste.Apply(stock);
  item.RecordWaste(waste);
  CHECK(item.Total()==610);
}

TEST_CASE("ThermalBag operations") {
  ThermalBag item;
  CHECK(item.GetCapacity()==3);
  CHECK(item.GetClean());
  CHECK_THROWS_AS(item.Unload(),UnavailableItem);
  item.Load(Pizza{});
  CHECK_THROWS_AS(item.Clean(),InvalidOrder);
  item.Load(Pizza{});
  item.Load(Pizza{});
  CHECK_THROWS_AS(item.Load(Pizza{}),UnavailableItem);
  CHECK(item.Unload().Price()==600);
  item.Unload();
  item.Unload();
  CHECK_FALSE(item.GetClean());
  CHECK_THROWS_AS(item.Load(Pizza{}),UnavailableItem);
  item.Clean();
  CHECK(item.GetClean());
}

TEST_CASE("DeliveryRoute operations") {
  DeliveryRoute item;
  CHECK(item.GetCapacity()==5);
  CHECK_FALSE(item.GetFinished());
  CHECK(item.TotalDistance()==0);
  CHECK_THROWS_AS(item.Finish(),InvalidOrder);
  for(int index=0;index<5;++index)item.AddStop(Address{});
  CHECK(item.TotalDistance()==15);
  CHECK_THROWS_AS(item.AddStop(Address{}),InvalidOrder);
  item.Finish();
  CHECK(item.GetFinished());
  CHECK_THROWS_AS(item.AddStop(Address{}),InvalidOrder);
  CHECK_THROWS_AS(item.Finish(),InvalidOrder);
}

TEST_CASE("SalesReport operations") {
  Order order;
  order.Add(OrderLine{});
  Payment payment;
  payment.Capture(order,600);
  SalesReport item;
  CHECK(item.GetOrders().empty());
  CHECK(item.GetPayments().empty());
  CHECK(item.AverageCheck()==0);
  Payment empty;
  CHECK_THROWS_AS(item.Record(order,empty),InvalidOrder);
  item.Record(order,payment);
  CHECK(item.Revenue()==600);
  CHECK(item.AverageCheck()==600);
}
