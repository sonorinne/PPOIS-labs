#pragma once
#include <string>
#include <vector>

class Pizza;

/// Печь.
class Oven {
 public:
  void Heat(int degrees);
  void Load(const Pizza& pizza);
  void Unload();
  int GetTemperature() const { return temperature_; }
  int GetRequiredTemperature() const { return required_temperature_; }
  int GetDiameter() const { return diameter_; }
  bool GetOccupied() const { return occupied_; }

 private:
  int temperature_ = 20;
  int required_temperature_ = 250;
  int diameter_ = 40;
  bool occupied_ = false;
};
