#pragma once
#include <string>
#include <vector>



/// Стол в зале.
class Table {
 public:
  void Seat(int guests);
  void Vacate();
  void Clean();
  int GetNumber() const { return number_; }
  int GetSeats() const { return seats_; }
  int GetGuests() const { return guests_; }
  bool GetClean() const { return clean_; }

 private:
  int number_ = 1;
  int seats_ = 4;
  int guests_ = 0;
  bool clean_ = true;
};
