#include "figure.hpp"

namespace lib::geometry {

std::ostream &operator<<(std::ostream &os, const Figure &f) {
  f.Print(os);
  return os;
}

std::istream &operator>>(std::istream &is, Figure &f) {
  f.Read(is);
  return is;
}
} // namespace lib::geometry
