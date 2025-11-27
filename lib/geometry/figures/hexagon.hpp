#pragma once

#include "figure.hpp"

namespace lib::geometry {

const std::size_t HEXAGONS_NUMBER_OF_VERTICES = 6;

class Hexagon : public Figure {
public:
  Hexagon() noexcept;

  Hexagon &operator=(const Hexagon &other);
  Hexagon &operator=(Hexagon &&other) noexcept;

  explicit operator double() const noexcept final;

  Point GetCenter() const noexcept final;

  virtual void Print(std::ostream &out) const final;
  virtual void Read(std::istream &i) final;

  friend bool operator==(const Hexagon &first, const Hexagon &second) noexcept;
  friend bool operator!=(const Hexagon &first, const Hexagon &second) noexcept;

private:
  Point points_[HEXAGONS_NUMBER_OF_VERTICES];
};
} // namespace lib::geometry
