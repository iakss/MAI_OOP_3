#pragma once

#include "figure.hpp"

namespace lib::geometry {

class Pentagon : public Figure {
public:
  static constexpr std::size_t NUMBER_OF_VERTICES = 5;

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
  Point points_[NUMBER_OF_VERTICES];
};
} // namespace lib::geometry
