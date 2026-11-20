#pragma once
#include <string>
#include <vector>
#include "Customer.h"


/// Отзыв клиента.
class Review {
 public:
  void Rate(int stars);
  void Write(const std::string& text);
  void Publish();
  const Customer& GetCustomer() const { return customer_; }
  int GetStars() const { return stars_; }
  const std::string& GetText() const { return text_; }
  bool GetPublished() const { return published_; }

 private:
  Customer customer_;
  int stars_ = 5;
  std::string text_ = "";
  bool published_ = false;
};
