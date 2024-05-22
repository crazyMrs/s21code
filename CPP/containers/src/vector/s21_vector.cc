#include "s21_vector.h"

template <class T>
s21::vector<T>::vector() noexcept : array_(nullptr), size_(0), capacity_(0) {}

template <class T>
s21::vector<T>::vector(size_type n) : size_(n), capacity_(n) {
  array_ = reinterpret_cast<T *>(new int8_t[sizeof(value_type) * capacity_]);
  for (size_type i = 0; i < size_; ++i) {
    new (array_ + i) value_type();
  }
}

template <class T>
s21::vector<T>::vector(std::initializer_list<value_type> const &items)
    : s21::vector<T>::vector(items.size()) {
  int count{0};
  for (value_type element : items) {
    array_[count] = element;
    ++count;
  }
}

template <class T>
s21::vector<T>::vector(vector &&v) noexcept
    : array_(std::move(v.array_)),
      size_(std::move(v.size_)),
      capacity_(std::move(v.capacity_)) {
  v.array_ = nullptr;
  v.capacity_ = 0;
  v.size_ = 0;
}

template <class T>
s21::vector<T>::vector(const vector &v) : s21::vector<T>::vector() {
  if (v.capacity_ != 0) {
    this->array_ = reinterpret_cast<value_type *>(
        new uint8_t[v.capacity_ * sizeof(value_type)]);
    this->capacity_ = v.capacity_;
  }
  if (v.size_ != 0) {
    for (size_type i{0}; i < v.size_; ++i) {
      new (this->array_ + i) value_type(v.array_[i]);
    }
    this->size_ = v.size_;
  }
}

template <class T>
s21::vector<T>::~vector() {
  if (array_ != nullptr) {
    clear();
    delete[] reinterpret_cast<uint8_t *>(array_);
  }
}

template <class T>
s21::vector<T> &s21::vector<T>::operator=(s21::vector<T> &&v) noexcept {
  array_ = std::move(v.array_);
  capacity_ = std::move(v.capacity_);
  size_ = std::move(v.size_);
  v.array_ = nullptr;
  v.capacity_ = 0;
  v.size_ = 0;

  return *this;
}

// Vector Iterators

template <class T>
typename s21::vector<T>::const_iterator s21::vector<T>::cbegin()
    const noexcept {
  return const_iterator(array_);
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::begin() noexcept {
  return iterator(array_);
}

template <class T>
typename s21::vector<T>::const_iterator s21::vector<T>::cend() const noexcept {
  return const_iterator(array_ + size_);
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::end() noexcept {
  return const_iterator(array_ + size_);
}

// Vector Capacity

template <class T>
bool s21::vector<T>::empty() const noexcept {
  return size_ ? false : true;
}

template <class T>
size_t s21::vector<T>::size() const noexcept {
  return size_;
}

template <class T>
size_t s21::vector<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

template <class T>
void s21::vector<T>::reserve(size_type size) {
  if (size <= size_) return;
  resize(size);
  capacity_ = size;
}

template <class T>
size_t s21::vector<T>::capacity() const noexcept {
  return capacity_;
}

template <class T>
void s21::vector<T>::shrink_to_fit() {
  if (size_ == capacity_) {
    return;
  }
  resize(size_);
  capacity_ = size_;
}

// Vector Element access

template <class T>
T &s21::vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Error in at()");
  }
  return array_[pos];
}

template <class T>
T &s21::vector<T>::operator[](size_type pos) {
  return array_[pos];
}

template <class T>
const T &s21::vector<T>::front() {
  return *(begin());
}

template <class T>
const T &s21::vector<T>::back() {
  return *(--end());
}

template <class T>
T *s21::vector<T>::data() noexcept {
  return &(*(this->begin()));
}

// Vector Modifiers

template <class T>
void s21::vector<T>::clear() noexcept {
  for (size_type i = 0; i < size_; ++i) {
    (array_ + i)->~T();
  }
  size_ = 0;
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::insert(
    const_iterator pos, const_reference value) {
  size_type index = pos - cbegin();
  if (!capacity_) {
    reserve(1);
  }
  if (capacity_ == size_) {
    reserve(capacity_ * 2);
  }
  for (size_type i = size_; i > index; --i) {
    array_[i] = array_[i - 1];
  }
  ++size_;
  iterator it = begin();
  it += index;
  *it = value;
  return it;
}

template <class T>
void s21::vector<T>::erase(iterator pos) {
  if (pos == end()) throw("Error");
  size_type index = pos - begin();
  if (size_ != 0) {
    for (size_type i = index; i < (size_ - 1); ++i) {
      array_[i] = array_[i + 1];
    }
  }
  pop_back();
}

template <class T>
void s21::vector<T>::push_back(const_reference value) {
  if (capacity_ * 2 > this->max_size()) {
    throw std::out_of_range("Error in memory from push_back()");
  }
  if (!capacity_) {
    reserve(1);
  }
  if (size_ == capacity_) {
    reserve(2 * capacity_);
  }
  new (array_ + size_) T(value);
  ++size_;
}

template <class T>
void s21::vector<T>::pop_back() {
  if (!size_) {
    return;
  }
  (array_ + (size_ - 1))->~T();
  --size_;
}

template <class T>
void s21::vector<T>::swap(vector &other) {
  std::swap(*this, other);
}

template <class T>
void s21::vector<T>::resize(size_type size) {
  T *new_arr = reinterpret_cast<T *>(new uint8_t[sizeof(value_type) * size]);
  for (size_type i = 0; i < size_; ++i) {
    new (new_arr + i) T(array_[i]);  // new placement
  }
  for (size_type i = 0; i < size_; ++i) {
    (array_ + i)->~T();
  }
  delete[] reinterpret_cast<uint8_t *>(array_);
  array_ = new_arr;
}

template <class T>
s21::vector<T>::iterator::iterator() : ptr(nullptr) {}

template <class T>
s21::vector<T>::iterator::iterator(T *p) : ptr(p) {}

template <class T>
T &s21::vector<T>::iterator::operator*() {
  return *ptr;
}

template <class T>
bool s21::vector<T>::iterator::operator!=(
    const s21::vector<T>::iterator &other) {
  return ptr != other.ptr;
}

template <class T>
bool s21::vector<T>::iterator::operator==(
    const s21::vector<T>::iterator &other) {
  return ptr == other.ptr;
}

template <class T>
typename s21::vector<T>::iterator &s21::vector<T>::iterator::operator++() {
  ++ptr;
  return *this;
}

template <class T>
typename s21::vector<T>::iterator &s21::vector<T>::iterator::operator--() {
  --ptr;
  return *this;
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::iterator::operator++(int) {
  auto copy_it = *this;
  ptr++;
  return copy_it;
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::iterator::operator--(int) {
  auto copy_it = *this;
  ptr--;
  return copy_it;
}

template <class T>
void s21::vector<T>::iterator::operator+=(const size_type &other) {
  ptr += other;
}

template <class T>
typename s21::vector<T>::size_type s21::vector<T>::iterator::operator-(
    const iterator &other) {
  return this->ptr - other.ptr;
}

template <class T>
s21::vector<T>::const_iterator::const_iterator() : iterator() {}

template <class T>
s21::vector<T>::const_iterator::const_iterator(T *p) : iterator(p) {}

template <class T>
const T &s21::vector<T>::const_iterator::operator*() {
  return s21::vector<T>::iterator::operator*();
}

template <class T>
typename s21::vector<T>::const_iterator &
s21::vector<T>::const_iterator::operator--() {
  --(this->ptr);
  return *this;
}

template <class T>
template <class... Args>
typename s21::vector<T>::iterator s21::vector<T>::insert_many(
    s21::vector<T>::const_iterator pos, Args &&...args) {
  vector<T> copy{args...};
  size_type before = pos - cbegin();
  iterator res;
  for (size_type i = 0; i < copy.size(); i++) {
    const_iterator copy_pos = cbegin();
    copy_pos += before++;
    res = insert(copy_pos, copy[i]);
  }
  ++res;
  return res;
}

template <class T>
template <class... Args>
void s21::vector<T>::insert_many_back(Args &&...args) {
  vector<T> copy{args...};
  for (auto it = copy.begin(); it != copy.end(); ++it) {
    push_back(*it);
  }
}
