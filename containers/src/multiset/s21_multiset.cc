#include "s21_multiset.h"

template <class Key>
s21::multiset<Key>::multiset() : s21::set<Key>() {}

template <class Key>
s21::multiset<Key>::multiset(const std::initializer_list<Key> &items) {
  for (auto value : items) {
    insert(value);
  }
}

template <class Key>
s21::multiset<Key>::multiset(const s21::multiset<Key> &ms)
    : s21::set<Key>(ms) {}

template <class Key>
s21::multiset<Key>::multiset(s21::multiset<Key> &&ms)
    : s21::set<Key>(std::move(ms)) {}

template <class Key>
s21::multiset<Key>::~multiset() {}

template <class Key>
s21::multiset<Key> &s21::multiset<Key>::operator=(
    s21::multiset<Key> &&ms) noexcept {
  s21::set<Key>::operator=(std::move(ms));
  return *this;
}

template <class Key>
void s21::multiset<Key>::merge(s21::multiset<Key> &other) {
  multiset<Key> copy_other(other);
  for (auto it = copy_other.begin(); it != copy_other.end(); ++it) {
    this->insert((*it));
    other.DeleteNode(other.root_, (*it));
  }
}

template <class Key>
std::pair<typename s21::multiset<Key>::iterator, bool>
s21::multiset<Key>::insert(const value_type &value) {
  this->AddNode(this->root_, std::make_pair(value, value));
  auto node = this->SearchNode(this->root_, value);
  iterator it(node, node->parent_);
  return {it, true};
}

template <class Key>
typename s21::multiset<Key>::size_type s21::multiset<Key>::count(
    const Key &key) {
  typename s21::set<Key>::size_type size{0};
  for (typename s21::multiset<int>::iterator it = this->begin();
       it != s21::set<Key>::end(); ++it) {
    if (*it == key) size++;
  }
  return size;
}

template <class Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::lower_bound(
    const Key &key) {
  if (this->SearchNode(this->root_, key) == nullptr) return this->end();
  typename s21::multiset<int>::iterator it = this->begin();
  for (; *it != key; ++it) {
  }
  return it;
}

template <class Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::upper_bound(
    const Key &key) {
  if (this->SearchNode(this->root_, key) == nullptr) return this->end();
  typename s21::multiset<int>::iterator it = this->end();
  for (; *it != key; --it) {
  }
  return ++it;
}

template <class Key>
std::pair<typename s21::multiset<Key>::iterator,
          typename s21::multiset<Key>::iterator>
s21::multiset<Key>::equal_range(const Key &key) {
  return {lower_bound(key), upper_bound(key)};
}

template <class Key>
template <class... Args>
std::vector<std::pair<typename s21::multiset<Key>::iterator, bool>>
s21::multiset<Key>::insert_many(Args &&...args) {
  multiset<Key> other{args...};
  std::vector<std::pair<iterator, bool>> result;
  for (auto it = other.begin(); it != other.end(); ++it) {
    result.push_back(insert(*it));
  }
  return result;
}