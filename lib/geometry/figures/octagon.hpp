#pragma once

#include "figure.hpp"

namespace lib::geometry {

class Octagon : public Figure {
public:
  static constexpr std::size_t number_of_vertices = 8;

  Octagon() noexcept;

  Octagon &operator=(const Octagon &other);
  Octagon &operator=(Octagon &&other) noexcept;

  explicit operator double() const noexcept final;

  Point GetCenter() const noexcept final;

  virtual void Print(std::ostream &out) const final;
  virtual void Read(std::istream &i) final;

  friend bool operator==(const Octagon &first, const Octagon &second) noexcept;
  friend bool operator!=(const Octagon &first, const Octagon &second) noexcept;

private:
  Point points_[number_of_vertices];
};
} // namespace lib::geometry
