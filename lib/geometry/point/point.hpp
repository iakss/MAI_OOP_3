#pragma once

#include <iostream>

namespace lib::geometry {

class Point {
public:
  Point() noexcept;
  Point(double x, double y) noexcept;

  Point &operator+=(const Point &other) noexcept;
  Point &operator-=(const Point &other) noexcept;
  Point &operator*=(const double number) noexcept;
  Point &operator/=(const double number) noexcept;
  explicit operator double() const noexcept;

public:
  double x;
  double y;
};

Point operator+(const Point &first, const Point &second) noexcept;
Point operator-(const Point &first, const Point &second) noexcept;
Point operator*(const double number, const Point &point) noexcept;
Point operator/(const Point &point, const double number) noexcept;

std::istream &operator>>(std::istream &is, Point &point);
std::ostream &operator<<(std::ostream &os, const Point &point);
} // namespace lib::geometry
