#pragma once

#include "figure.hpp"

#include <initializer_list>

namespace lib::array {

const std::size_t DEFAULT_CAPACITY = 10;

class Array {
public:
  Array() noexcept;
  Array(const std::initializer_list<geometry::Figure *> &init);

  Array(const Array &other);
  Array(Array &&other) noexcept;
  ~Array() noexcept;

  Array &operator=(const Array &other);
  Array &operator=(Array &&other) noexcept;

  geometry::Figure *operator[](std::size_t pos) noexcept;
  geometry::Figure *const operator[](std::size_t pos) const noexcept;

  geometry::Figure *const Front() const noexcept;
  geometry::Figure *Front() noexcept;
  geometry::Figure *const Back() const noexcept;
  geometry::Figure *Back() noexcept;
  geometry::Figure *const *Data() const noexcept;
  geometry::Figure **Data() noexcept;

  bool Empty() const noexcept;
  std::size_t Size() const noexcept;
  void Reserve(const std::size_t new_cap);
  std::size_t Capacity() const noexcept;

  void Clear() noexcept;
  void PushBack(geometry::Figure *value);
  void PopBack() noexcept;

  void Insert(std::size_t pos, geometry::Figure *value);
  void Erase(std::size_t pos);

  void PrintCenters() const noexcept;
  void PrintAreas() const noexcept;
  double GetTotalArea() const noexcept;

  friend void swap(Array &first, Array &second) noexcept;

private:
  std::size_t capacity_ = 0;
  std::size_t size_ = 0;
  geometry::Figure **data_ = nullptr;
};

} // namespace lib::array
