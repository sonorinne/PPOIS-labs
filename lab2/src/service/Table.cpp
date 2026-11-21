#include "Table.h"

#include "InvalidReservation.h"

void Table::Seat(int guests) {
  if (guests <= 0 || guests > seats_ || guests_ > 0 || !clean_) throw InvalidReservation();
  guests_ = guests;
}

void Table::Vacate() {
  if (guests_ == 0) throw InvalidReservation();
  guests_ = 0;
  clean_ = false;
}

void Table::Clean() {
  if (guests_ > 0) throw InvalidReservation();
  clean_ = true;
}
