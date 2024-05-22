
#ifndef CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_

#include <iostream>
#include <limits>
#include <vector>

#include "../base_tree/s21_BaseTree.h"

namespace s21 {
template <class Key>
class set : public BaseTree<Key, Key> {
 public:
  class SetIterator;
  class ConstSetIterator;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = SetIterator;
  using const_iterator = ConstSetIterator;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set();
  set& operator=(set&& s) noexcept;

  // Set Iterators
  iterator begin();
  iterator end();

  // Set Capacity
  bool empty() const noexcept;
  size_type size();
  size_type max_size();

  // Set Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  // Set Lookup
  iterator find(const Key& key);
  bool contains(const Key& key);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  class SetIterator : public BaseTree<Key, Key>::BaseTreeIterator {
   public:
    SetIterator();
    SetIterator(typename BaseTree<Key, Key>::Node* node,
                typename BaseTree<Key, Key>::Node* prev_node);
    const value_type& operator*();
    SetIterator& operator++();
    SetIterator operator++(int);
    SetIterator& operator--();
    SetIterator operator--(int);
  };
  class ConstSetIterator : SetIterator {};
};
}  // namespace s21

#include "s21_set.cc"
#endif  // CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_