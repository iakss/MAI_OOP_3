#pragma once

#include "figure.hpp"

namespace lib::geometry {

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
  static constexpr std::size_t number_of_vertices = 6;
  Point points_[number_of_vertices];
};
} // namespace lib::geometry
