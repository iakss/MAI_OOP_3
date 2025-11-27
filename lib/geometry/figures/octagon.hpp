#pragma once

#include "figure.hpp"

namespace lib::geometry {

const std::size_t OCTAGONS_NUMBER_OF_VERTICES = 8;

class Octagon : public Figure {
public:
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
  Point points_[OCTAGONS_NUMBER_OF_VERTICES];
};
} // namespace lib::geometry
