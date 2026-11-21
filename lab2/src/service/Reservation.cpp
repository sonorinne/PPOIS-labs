#include "Reservation.h"
#include "Customer.h"
#include "Table.h"
#include "InvalidReservation.h"

void Reservation::CheckIn(Table& table) {
  if (!active_) throw InvalidReservation();
  table.Seat(guests_);
  active_ = false;
}

void Reservation::Postpone(int minutes) {
  if (!active_ || minutes <= 0) throw InvalidReservation();
  minute_ += minutes;
}

void Reservation::Cancel() {
  if (!active_) throw InvalidReservation();
  active_ = false;
}
