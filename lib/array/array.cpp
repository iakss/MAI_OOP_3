#include "array.hpp"

#include <cstring>

namespace lib::array {

Array::Array() noexcept = default;

Array::Array(const std::initializer_list<geometry::Figure *> &init) {
  if (init.size() > 0) {
    Reserve(init.size());
    size_ = init.size();
    size_t index = 0;
    for (geometry::Figure *i : init) {
      data_[index] = i;
      ++index;
    }
  }
}

Array::Array(const Array &other) {
  Reserve(other.capacity_);
  size_ = other.size_;
  for (std::size_t i = 0; i < other.size_; ++i) {
    data_[i] = other.data_[i];
  }
}

Array::Array(Array &&other) noexcept
    : capacity_(other.capacity_), size_(other.size_), data_(other.data_) {
  other.capacity_ = 0;
  other.size_ = 0;
  other.data_ = nullptr;
}

Array::~Array() noexcept { delete[] data_; }

Array &Array::operator=(const Array &other) {
  if (this != &other) {
    Array temp(other);
    swap(*this, temp);
  }
  return *this;
}

Array &Array::operator=(Array &&other) noexcept {
  if (this != &other) {
    Array temp = std::move(other);
    swap(*this, temp);
  }
  return *this;
}

geometry::Figure *Array::Front() noexcept { return data_[0]; }

geometry::Figure *const Array::Front() const noexcept { return data_[0]; }

geometry::Figure *Array::Back() noexcept { return data_[size_ - 1]; }

geometry::Figure *const Array::Back() const noexcept {
  return data_[size_ - 1];
}

geometry::Figure **Array::Data() noexcept { return data_; }

geometry::Figure *const *Array::Data() const noexcept { return data_; }

bool Array::Empty() const noexcept { return size_ == 0; }

std::size_t Array::Size() const noexcept { return size_; }

void Array::Reserve(const std::size_t new_cap) {
  if (capacity_ < new_cap or capacity_ == 0) {
    const std::size_t to_alloc_cap = std::max(new_cap, DEFAULT_CAPACITY);
    geometry::Figure **new_data = new geometry::Figure *[to_alloc_cap];
    if (data_) {
      std::memcpy(new_data, data_, size_);
      delete[] data_;
    }
    capacity_ = to_alloc_cap;
    data_ = new_data;
  }
}

std::size_t Array::Capacity() const noexcept { return capacity_; }

void Array::Clear() noexcept {
  for (std::size_t i = 0; i < size_; ++i) {
    data_[i] = 0;
  }
  size_ = 0;
}

void Array::PushBack(geometry::Figure *value) {
  if (size_ == capacity_) {
    Reserve(size_ * 2);
  }
  data_[size_] = value;
  ++size_;
}

void Array::PopBack() noexcept {
  if (size_ > 0) {
    data_[size_ - 1] = 0;
    --size_;
  }
}

void Array::Insert(std::size_t pos, geometry::Figure *value) {
  if (size_ == capacity_) {
    Reserve(size_ * 2);
  }
  for (std::size_t i = size_; i > pos; --i) {
    data_[i] = data_[i - 1];
  }
  data_[pos] = value;
  ++size_;
}

void Array::Erase(std::size_t pos) {
  for (std::size_t i = pos; i + 1 < size_; ++i) {
    data_[i] = data_[i + 1];
  }
  --size_;
}

void Array::PrintCenters() const noexcept {
  for (std::size_t i = 0; i < size_; ++i) {
    std::cout << i + 1 << "Figure center: " << data_[i]->GetCenter()
              << std::endl;
  }
}

void Array::PrintAreas() const noexcept {
  for (std::size_t i = 0; i < size_; ++i) {
    std::cout << i + 1 << "Figure area: " << static_cast<double>(*data_[i])
              << std::endl;
  }
}

double Array::GetTotalArea() const noexcept {
  double total_area = 0;
  for (std::size_t i = 0; i < size_; ++i) {
    total_area += static_cast<double>(*data_[i]);
  }
  return total_area;
}

void swap(Array &first, Array &second) noexcept {
  using std::swap;
  swap(first.capacity_, second.capacity_);
  swap(first.size_, second.size_);
  swap(first.data_, second.data_);
}

} // namespace lib::array
