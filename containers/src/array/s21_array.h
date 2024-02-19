#ifndef CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() : size_(N) {}

  array(std::initializer_list<value_type> const &items) : array() {
    for (size_type i = 0; i < items.size(); i++) {
      arr_[i] = *(items.begin() + i);
    }
  }

  array(const array &a) {
    for (size_type i = 0; i < size_; ++i) {
      arr_[i] = a.arr_[i];
    }
  }

  array(array &&a) noexcept : size_(a.size_) {
    std::move(a.arr_, a.arr_ + size_, arr_);
  }

  ~array() {}

  array<T, N> &operator=(array &&a) noexcept {
    if (this != &a) {
      std::move(a.arr_, a.arr_ + size_, arr_);
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_ || size_ == 0) {
      throw std::out_of_range("Index out range");
    }
    return arr_[pos];
  }

  reference operator[](size_type pos) { return *(arr_ + pos); }

  const_reference front() { return *arr_; }
  const_reference back() { return arr_[size_ - 1]; }
  iterator data() { return arr_; }

  iterator begin() noexcept { return arr_; }
  const_iterator begin() const noexcept { return arr_; }

  iterator end() noexcept { return arr_ + size_; }
  const_iterator end() const noexcept { return arr_ + size_; }

  bool empty() { return size_ == 0; }

  size_type size() { return size_; }

  size_type max_size() { return size(); }

  void swap(array &other) {
    for (size_type i = 0; i < size_; ++i) {
      std::swap(other.arr_[i], arr_[i]);
    }
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < size_; ++i) {
      arr_[i] = value;
    }
  }

 private:
  size_type size_ = N;
  value_type arr_[N];
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_