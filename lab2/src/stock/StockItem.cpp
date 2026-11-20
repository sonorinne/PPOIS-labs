#include "StockItem.h"
#include "Ingredient.h"
#include "PurchaseLine.h"
#include "InvalidQuantity.h"
#include "StockShortage.h"
#include "UnavailableItem.h"

void StockItem::Receive(const PurchaseLine& line) {
  if (line.GetIngredient().GetName() != ingredient_.GetName()) throw UnavailableItem();
  if (line.GetReceived() <= 0) throw InvalidQuantity();
  grams_ += line.GetReceived();
}

void StockItem::Consume(int grams) {
  if (grams <= 0) throw InvalidQuantity();
  if (grams > grams_) throw StockShortage();
  grams_ -= grams;
}

void StockItem::Discard(int grams) {
  Consume(grams);
  wasted_ += grams;
}

void StockItem::Merge(const StockItem& other) {
  if (ingredient_.GetName() != other.ingredient_.GetName()) throw UnavailableItem();
  grams_ += other.grams_;
}
