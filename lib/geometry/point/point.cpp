#include "point.hpp"

#include <cmath>

namespace lib::geometry {

Point::Point() noexcept : x(0), y(0) {}

Point::Point(double x, double y) noexcept : x(x), y(y) {}

Point &Point::operator+=(const Point &other) noexcept {
  x += other.x;
  y += other.y;
  return *this;
}

Point &Point::operator-=(const Point &other) noexcept {
  x -= other.x;
  y -= other.y;
  return *this;
}

Point &Point::operator*=(const double number) noexcept {
  x *= number;
  y *= number;
  return *this;
}

Point &Point::operator/=(const double number) noexcept {
  x /= number;
  y /= number;
  return *this;
}

Point::operator double() const noexcept {
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

Point operator+(const Point &first, const Point &second) noexcept {
  return Point(first.x + second.x, first.y + second.y);
}

Point operator-(const Point &first, const Point &second) noexcept {
  return Point(first.x - second.x, first.y - second.y);
}

Point operator*(const double number, const Point &point) noexcept {
  return Point(number * point.x, number * point.y);
}

Point operator*(const Point &point, const double number) noexcept {
  return number * point;
}

Point operator/(const Point &point, const double number) noexcept {
  return Point(point.x / number, point.y / number);
}

bool operator==(const Point &first, const Point &second) noexcept {
  return std::fabs(static_cast<double>(first - second)) < Point::EPS;
}

bool operator!=(const Point &first, const Point &second) noexcept {
  return !(first == second);
}

std::istream &operator>>(std::istream &is, Point &point) {
  is >> point.x;
  is >> point.y;
  return is;
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
  os << "(" << point.x << ", " << point.y << ")";
  return os;
}
} // namespace lib::geometry
