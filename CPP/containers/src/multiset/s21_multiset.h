#ifndef CPP2_S21_CONTAINERS_SRC_MULTISET_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_SRC_MULTISET_S21_MULTISET_H_

#include <iostream>

#include "../set/s21_set.h"

namespace s21 {
template <class Key>
class multiset : public s21::set<Key> {
 public:
  using iterator = typename s21::set<Key>::iterator;
  using const_iterator = typename s21::set<Key>::const_iterator;
  using size_type = typename s21::set<Key>::size_type;
  using value_type = typename s21::set<Key>::value_type;
  multiset();
  multiset(std::initializer_list<Key> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset();
  multiset& operator=(multiset&& ms) noexcept;

  void merge(multiset& other);
  std::pair<iterator, bool> insert(const value_type& value);
  size_type count(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};
}  // namespace s21

#include "s21_multiset.cc"
#endif  // CPP2_S21_CONTAINERS_SRC_MULTISET_S21_MULTISET_H_