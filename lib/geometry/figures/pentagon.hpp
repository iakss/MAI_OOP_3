#pragma once

#include "figure.hpp"

namespace lib::geometry {

const std::size_t PENTAGONS_NUMBER_OF_VERTICES = 5;

class Pentagon : public Figure {
public:
  Pentagon() noexcept;

  Pentagon &operator=(const Pentagon &other);
  Pentagon &operator=(Pentagon &&other) noexcept;

  explicit operator double() const noexcept final;

  Point GetCenter() const noexcept final;

  virtual void Print(std::ostream &os) const final;
  virtual void Read(std::istream &is) final;

  friend bool operator==(const Pentagon &first,
                         const Pentagon &second) noexcept;
  friend bool operator!=(const Pentagon &first,
                         const Pentagon &second) noexcept;

private:
  Point points_[PENTAGONS_NUMBER_OF_VERTICES];
};
} // namespace lib::geometry
