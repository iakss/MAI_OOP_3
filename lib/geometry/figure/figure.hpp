#pragma once

#include "point.hpp"

namespace lib::geometry {

class Figure {
public:
  virtual explicit operator double() const noexcept = 0;

  virtual Point GetCenter() const noexcept = 0;

  virtual void Print(std::ostream &os) const = 0;
  virtual void Read(std::istream &is) = 0;

  friend std::ostream &operator<<(std::ostream &os, const Figure &f);
  friend std::istream &operator>>(std::istream &is, Figure &f);
};

std::ostream &operator<<(std::ostream &os, const Figure &f);
std::istream &operator>>(std::istream &is, Figure &f);
} // namespace lib::geometry
