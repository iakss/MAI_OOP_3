#pragma once

#include "point.hpp"

namespace lib::geometry {

class Figure {
public:
  virtual explicit operator double() const noexcept;

  virtual Point GetCenter() const noexcept;

  virtual void Print(std::ostream &os) const;
  virtual void Read(std::istream &is);

  friend std::ostream &operator<<(std::ostream &os, const Figure &f);
  friend std::istream &operator>>(std::istream &is, Figure &f);
};
} // namespace lib::geometry
