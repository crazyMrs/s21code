#ifndef CPP2_S21_CONTAINERS_SRC_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_SRC_MAP_S21_MAP_H_

#include <iostream>
#include <limits>
#include <vector>

#include "../base_tree/s21_BaseTree.h"

namespace s21 {

template <class Key, class T>
class map : public s21::BaseTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename s21::BaseTree<Key, T>::iterator;
  using const_iterator = typename s21::BaseTree<Key, T>::const_iterator;
  using size_type = size_t;

  // Map Member functions
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  ~map();
  map& operator=(map&& m) noexcept;
  map& operator=(map& m);

  // Map Element access
  T& at(const Key& key);
  T& operator[](const Key& key);

  // Map Iterators
  iterator begin();
  iterator end();

  // Map Capacity
  bool empty() const noexcept;
  size_type size() noexcept;
  size_type max_size() const noexcept;

  // Map Modifiers
  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos) noexcept;
  void swap(s21::map<Key, T>& other) noexcept;
  void merge(map& other);

  // Map Lookup
  bool contains(const Key& key) const;

  // Dop
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};
}  // namespace s21

#include "s21_map.cc"
#endif  // CPP2_S21_CONTAINERS_SRC_MAP_S21_MAP_H_