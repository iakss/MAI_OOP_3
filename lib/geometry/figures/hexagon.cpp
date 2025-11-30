#include "hexagon.hpp"

#include <cmath>

namespace {
double GetHexagonsArea(const lib::geometry::Point &first,
                       const lib::geometry::Point &second) noexcept {
  return 3 * sqrt(3) *
         std::pow(std::fabs(static_cast<double>(first - second)), 2) / 2;
}
} // namespace

namespace lib::geometry {

Hexagon::Hexagon() noexcept = default;

Hexagon &Hexagon::operator=(const Hexagon &) = default;
Hexagon &Hexagon::operator=(Hexagon &&) noexcept = default;

Hexagon::operator double() const noexcept {
  return GetHexagonsArea(points_[0], points_[1]);
}

Point Hexagon::GetCenter() const noexcept {
  Point point_sum = Point();
  for (size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    point_sum += points_[i];
  }
  return point_sum / Hexagon::NUMBER_OF_VERTICES;
}

// I assume that all the vercites are always enterted in the same order
bool operator==(const Hexagon &first, const Hexagon &second) noexcept {
  for (std::size_t i = 0; i < Hexagon::NUMBER_OF_VERTICES; ++i) {
    if (first.points_[i] != second.points_[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const Hexagon &first, const Hexagon &second) noexcept {
  return !(first == second);
}

void Hexagon::Print(std::ostream &os) const {
  os << "Hexagon's vertices: ";
  for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    os << points_[i];
  }
}

void Hexagon::Read(std::istream &is) {
  for (size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    is >> points_[i];
  }
}
} // namespace lib::geometry
