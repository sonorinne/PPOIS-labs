#pragma once
#include <string>
#include <vector>
#include "MenuItem.h"


/// Доступное меню.
class Menu {
 public:
  void Add(const MenuItem& item);
  const MenuItem& Find(const std::string& name) const;
  void Close();
  const std::vector<MenuItem>& GetItems() const { return items_; }
  int GetRevision() const { return revision_; }
  bool GetOpen() const { return open_; }
  const std::string& GetTitle() const { return title_; }

 private:
  std::vector<MenuItem> items_;
  int revision_ = 0;
  bool open_ = true;
  std::string title_ = "Pizzeria";
};
