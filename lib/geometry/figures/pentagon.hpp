#pragma once

#include "figure.hpp"

namespace lib::geometry {

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
  static constexpr std::size_t number_of_vertices = 5;
  Point points_[number_of_vertices];
};
} // namespace lib::geometry
