#include "Menu.h"
#include "MenuItem.h"
#include "UnavailableItem.h"

void Menu::Add(const MenuItem& item) {
  if (!open_) throw UnavailableItem();
  items_.push_back(item);
  ++revision_;
}

const MenuItem& Menu::Find(const std::string& name) const {
  for (const auto& item : items_) {
    if (item.GetName() == name) return item;
  }
  throw UnavailableItem();
}

void Menu::Close() {
  open_ = false;
  ++revision_;
}
