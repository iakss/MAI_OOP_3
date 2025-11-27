#include "pentagon.hpp"

#include <cmath>

namespace {
double GetPentagonsArea(const lib::geometry::Point &first,
                        const lib::geometry::Point &second) noexcept {
  return std::pow(std::fabs(static_cast<double>(first - second)), 2) *
         std::sqrt(25 + 10 * std::sqrt(5)) / 4;
}
} // namespace

namespace lib::geometry {

Pentagon::Pentagon() noexcept = default;

Pentagon &Pentagon::operator=(const Pentagon &) = default;
Pentagon &Pentagon::operator=(Pentagon &&) noexcept = default;

Pentagon::operator double() const noexcept {
  return GetPentagonsArea(points_[0], points_[1]);
}

Point Pentagon::GetCenter() const noexcept {
  Point point_sum = Point();
  for (size_t i = 0; i < PENTAGONS_NUMBER_OF_VERTICES; ++i) {
    point_sum += points_[i];
  }
  return point_sum / PENTAGONS_NUMBER_OF_VERTICES;
}

void Pentagon::Print(std::ostream &os) const {
  os << "Pentagon's vertices: ";
  for (std::size_t i = 0; i < PENTAGONS_NUMBER_OF_VERTICES; ++i) {
    os << points_[i];
  }
}

void Pentagon::Read(std::istream &is) {
  for (size_t i = 0; i < PENTAGONS_NUMBER_OF_VERTICES; ++i) {
    is >> points_[i];
  }
}
} // namespace lib::geometry
