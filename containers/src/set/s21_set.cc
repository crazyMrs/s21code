#include "s21_set.h"

template <class Key>
s21::set<Key>::set() : BaseTree<Key, Key>::BaseTree() {}

template <class Key>
s21::set<Key>::set(const std::initializer_list<Key> &items) : set() {
  for (auto value : items) {
    insert(value);
  }
}

template <class Key>
s21::set<Key>::set(const s21::set<Key> &s) : set() {
  BaseTree<Key, Key>::CopyTree(&(BaseTree<Key, Key>::root_),
                               s.BaseTree<Key, Key>::root_);
}

template <class Key>
s21::set<Key>::set(s21::set<Key> &&s) {
  BaseTree<Key, Key>::root_ = std::move(s.BaseTree<Key, Key>::root_);
  s.BaseTree<Key, Key>::root_ = nullptr;
}

template <class Key>
s21::set<Key>::~set() {
  BaseTree<Key, Key>::FreeNode(BaseTree<Key, Key>::root_);
}

template <class Key>
s21::set<Key> &s21::set<Key>::operator=(s21::set<Key> &&s) noexcept {
  if (this != &s) {
    BaseTree<Key, Key>::FreeNode(BaseTree<Key, Key>::root_);
    BaseTree<Key, Key>::root_ = std::move(s.BaseTree<Key, Key>::root_);
    s.BaseTree<Key, Key>::root_ = nullptr;
  }
  return *this;
}

// Set Iterators
template <class Key>
typename s21::set<Key>::iterator s21::set<Key>::begin() {
  return iterator(BaseTree<Key, Key>::GetMin(BaseTree<Key, Key>::root_),
                  nullptr);
}

template <class Key>
typename s21::set<Key>::iterator s21::set<Key>::end() {
  if (BaseTree<Key, Key>::root_ == nullptr) {
    return begin();
  }
  return iterator(nullptr,
                  BaseTree<Key, Key>::GetMax(BaseTree<Key, Key>::root_));
}

// Set Capasity
template <class Key>
bool s21::set<Key>::empty() const noexcept {
  return BaseTree<Key, Key>::root_ == nullptr ? true : false;
}

template <class Key>
size_t s21::set<Key>::size() {
  return BaseTree<Key, Key>::root_ == nullptr
             ? 0
             : BaseTree<Key, Key>::GetSize(BaseTree<Key, Key>::root_);
}

template <class Key>
size_t s21::set<Key>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 4;
}

// Set Modifiers
template <class Key>
void s21::set<Key>::clear() {
  BaseTree<Key, Key>::FreeNode(BaseTree<Key, Key>::root_);
  BaseTree<Key, Key>::root_ = nullptr;
}

template <class Key>
std::pair<typename s21::set<Key>::iterator, bool> s21::set<Key>::insert(
    const Key &value) {
  typename BaseTree<Key, Key>::Node *new_node =
      BaseTree<Key, Key>::SearchNode(BaseTree<Key, Key>::root_, value);
  bool happened = true;
  if (new_node != nullptr)
    happened = false;
  else {
    BaseTree<Key, Key>::AddNode(BaseTree<Key, Key>::root_,
                                std::make_pair(value, value));
    new_node = BaseTree<Key, Key>::SearchNode(BaseTree<Key, Key>::root_, value);
  }
  s21::set<Key>::iterator it(new_node, new_node->parent_);
  return {it, happened};
}

template <class Key>
void s21::set<Key>::erase(s21::set<Key>::iterator pos) {
  BaseTree<Key, Key>::DeleteNode(BaseTree<Key, Key>::root_, (*pos));
}

template <class Key>
void s21::set<Key>::swap(s21::set<Key> &other) {
  typename BaseTree<Key, Key>::Node *copy_root = BaseTree<Key, Key>::root_;
  BaseTree<Key, Key>::root_ = other.BaseTree<Key, Key>::root_;
  other.BaseTree<Key, Key>::root_ = copy_root;
}

template <class Key>
void s21::set<Key>::merge(s21::set<Key> &other) {
  set<Key> copy_other(other);
  for (auto it = copy_other.begin(); it != copy_other.end(); ++it) {
    if (BaseTree<Key, Key>::SearchNode(BaseTree<Key, Key>::root_, (*it)) ==
        nullptr) {
      this->insert((*it));
      other.BaseTree<Key, Key>::DeleteNode(other.BaseTree<Key, Key>::root_,
                                           (*it));
    }
  }
}

// Set Lookup
template <class Key>
typename s21::set<Key>::iterator s21::set<Key>::find(const Key &key) {
  typename BaseTree<Key, Key>::Node *result =
      BaseTree<Key, Key>::SearchNode(BaseTree<Key, Key>::root_, key);
  return result == nullptr ? s21::set<Key>::iterator(result, result->parent_)
                           : end();
}

template <class Key>
bool s21::set<Key>::contains(const Key &key) {
  typename BaseTree<Key, Key>::Node *result =
      BaseTree<Key, Key>::SearchNode(BaseTree<Key, Key>::root_, key);
  return result != nullptr ? true : false;
}

template <class Key>
template <class... Args>
std::vector<std::pair<typename s21::set<Key>::iterator, bool>>
s21::set<Key>::insert_many(Args &&...args) {
  set<Key> other{args...};
  std::vector<std::pair<typename s21::set<Key>::iterator, bool>> result;
  for (auto it = other.begin(); it != other.end(); ++it) {
    result.push_back(insert(*it));
  }
  return result;
}

template <class Key>
s21::set<Key>::SetIterator::SetIterator()
    : BaseTree<Key, Key>::BaseTreeIterator::BaseTreeIterator() {}

template <class Key>
s21::set<Key>::SetIterator::SetIterator(
    typename s21::BaseTree<Key, Key>::Node *node,
    typename s21::BaseTree<Key, Key>::Node *prev_node)
    : BaseTree<Key, Key>::BaseTreeIterator::BaseTreeIterator(node, prev_node) {}

template <class Key>
const Key &s21::set<Key>::SetIterator::operator*() {
  if (BaseTree<Key, Key>::BaseTreeIterator::node_ == nullptr) {
    static value_type result;
    return result;
  }
  return BaseTree<Key, Key>::BaseTreeIterator::node_->value_.second;
}

template <class Key>
typename s21::set<Key>::SetIterator &s21::set<Key>::SetIterator::operator++() {
  typename BaseTree<Key, Key>::BaseTreeIterator &it = *this;
  ++it;
  return *this;
}

template <class Key>
typename s21::set<Key>::SetIterator s21::set<Key>::SetIterator::operator++(
    int) {
  SetIterator copy = *this;
  ++(*this);
  return copy;
}

template <class Key>
typename s21::set<Key>::SetIterator &s21::set<Key>::SetIterator::operator--() {
  typename BaseTree<Key, Key>::BaseTreeIterator &it = *this;
  --it;
  return *this;
}

template <class Key>
typename s21::set<Key>::SetIterator s21::set<Key>::SetIterator::operator--(
    int) {
  SetIterator copy = *this;
  ++(*this);
  return copy;
}