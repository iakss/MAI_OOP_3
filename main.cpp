#include "array.hpp"
#include "figure.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"

#include <iostream>

int main() {
  lib::array::Array arr{};
  arr.PushBack(new lib::geometry::Pentagon());
  arr.PushBack(new lib::geometry::Hexagon());
  arr.PushBack(new lib::geometry::Octagon());

  for (std::size_t i = 0; i < 3; ++i) {
    std::cin >> *arr[i];
  }

  for (std::size_t i = 0; i < 3; ++i) {
    std::cout << *arr[i] << std::endl;
  }

  arr.PrintCenters();
  arr.PrintAreas();
  std::cout << arr.GetTotalArea();

  for (std::size_t i = 0; i < arr.Size(); ++i) {
    delete arr[i];
  }
}
