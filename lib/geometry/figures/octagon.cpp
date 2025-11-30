#include "octagon.hpp"

#include <cmath>

namespace {
double GetOctagonsArea(const lib::geometry::Point &first,
                       const lib::geometry::Point &second) noexcept {
  return 2 * std::pow(std::fabs(static_cast<double>(first - second)), 2) *
         (std::sqrt(2) + 1);
}
} // namespace

namespace lib::geometry {

Octagon::Octagon() noexcept = default;

Octagon &Octagon::operator=(const Octagon &) = default;
Octagon &Octagon::operator=(Octagon &&) noexcept = default;

Octagon::operator double() const noexcept {
  return GetOctagonsArea(points_[0], points_[1]);
}

Point Octagon::GetCenter() const noexcept {
  Point point_sum = Point();
  for (size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    point_sum += points_[i];
  }
  return point_sum / NUMBER_OF_VERTICES;
}

// I assume that all the vercites are always enterted in the same order
bool operator==(const Octagon &first, const Octagon &second) noexcept {
  for (std::size_t i = 0; i < Octagon::NUMBER_OF_VERTICES; ++i) {
    if (first.points_[i] != second.points_[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const Octagon &first, const Octagon &second) noexcept {
  return !(first == second);
}

void Octagon::Print(std::ostream &os) const {
  os << "Octagon's vertices: ";
  for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    os << points_[i];
  }
}

void Octagon::Read(std::istream &is) {
  for (size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    is >> points_[i];
  }
}
} // namespace lib::geometry
