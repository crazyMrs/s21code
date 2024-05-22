#include "s21_map.h"

/*
Map Member functions
*/

template <class Key, class T>
s21::map<Key, T>::map() : BaseTree<Key, T>::BaseTree() {}

template <class Key, class T>
s21::map<Key, T>::map(const std::initializer_list<value_type> &items) : map() {
  for (const std::pair<const Key, T> &value : items) {
    insert(value);
  }
}

template <class Key, class T>
s21::map<Key, T>::map(const map &m) : map() {
  s21::BaseTree<Key, T>::CopyTree(&(BaseTree<Key, T>::root_),
                                  m.BaseTree<Key, T>::root_);
}

template <class Key, class T>
s21::map<Key, T>::map(s21::map<Key, T> &&m) {
  BaseTree<Key, T>::root_ = std::move(m.BaseTree<Key, T>::root_);
  m.BaseTree<Key, T>::root_ = nullptr;
}

template <class Key, class T>
s21::map<Key, T>::~map() {
  BaseTree<Key, T>::FreeNode(BaseTree<Key, T>::root_);
}

template <class Key, class T>
s21::map<Key, T> &s21::map<Key, T>::operator=(s21::map<Key, T> &&m) noexcept {
  BaseTree<Key, T>::FreeNode(BaseTree<Key, T>::root_);
  BaseTree<Key, T>::root_ = std::move(m.BaseTree<Key, T>::root_);
  m.BaseTree<Key, T>::root_ = nullptr;
  return *this;
}

template <class Key, class T>
s21::map<Key, T> &s21::map<Key, T>::operator=(s21::map<Key, T> &m) {
  BaseTree<Key, T>::FreeNode(BaseTree<Key, T>::root_);
  s21::BaseTree<Key, T>::CopyTree(&(BaseTree<Key, T>::root_), m);
  return *this;
}

/*
Map Element access
*/

template <class Key, class T>
T &s21::map<Key, T>::at(const Key &key) {
  typename BaseTree<Key, T>::Node *node =
      BaseTree<Key, T>::SearchNode(BaseTree<Key, T>::root_, key);
  if (node == nullptr) {
    throw std::out_of_range("Error in at()!");
  }
  return node->value_.second;
}

template <class Key, class T>
T &s21::map<Key, T>::operator[](const Key &key) {
  typename BaseTree<Key, T>::Node *node =
      BaseTree<Key, T>::SearchNode(BaseTree<Key, T>::root_, key);
  if (node == nullptr) {
    return (*(insert_or_assign(key, 0).first)).second;
  }
  return (BaseTree<Key, T>::SearchNode(BaseTree<Key, T>::root_, key))
      ->value_.second;
}

/*
Map Modifiers
*/

template <class Key, class T>
void s21::map<Key, T>::clear() noexcept {
  BaseTree<Key, T>::FreeNode(BaseTree<Key, T>::root_);
  BaseTree<Key, T>::root_ = nullptr;
}

template <class Key, class T>
std::pair<typename s21::map<Key, T>::iterator, bool> s21::map<Key, T>::insert(
    const std::pair<const Key, T> &value) {
  typename BaseTree<Key, T>::Node *new_node =
      BaseTree<Key, T>::SearchNode(BaseTree<Key, T>::root_, value.first);
  bool happened = true;
  if (new_node != nullptr)
    happened = false;
  else {
    BaseTree<Key, T>::AddNode(BaseTree<Key, T>::root_, value);
    new_node =
        BaseTree<Key, T>::SearchNode(BaseTree<Key, T>::root_, value.first);
  }
  iterator it(new_node, new_node->parent_);
  return {it, happened};
}

template <class Key, class T>
std::pair<typename s21::map<Key, T>::iterator, bool> s21::map<Key, T>::insert(
    const Key &key, const T &obj) {
  return insert({key, obj});
}

template <class Key, class T>
std::pair<typename s21::map<Key, T>::iterator, bool>
s21::map<Key, T>::insert_or_assign(const Key &key, const T &obj) {
  typename BaseTree<Key, T>::Node *new_node =
      BaseTree<Key, T>::SearchNode(BaseTree<Key, T>::root_, key);
  bool happened = true;
  std::pair<Key, T> value{key, obj};
  if (new_node != nullptr) {
    new_node->value_.second = obj;
    happened = false;
  } else {
    BaseTree<Key, T>::AddNode(BaseTree<Key, T>::root_, value);
    new_node = BaseTree<Key, T>::SearchNode(BaseTree<Key, T>::root_, key);
  }
  s21::map<Key, T>::iterator it(new_node, new_node->parent_);
  return {it, happened};
}

template <class Key, class T>
void s21::map<Key, T>::erase(iterator pos) noexcept {
  // std::cout << (*pos).first << std::endl;
  BaseTree<Key, T>::DeleteNode(BaseTree<Key, T>::root_, (*pos).first);
}

template <class Key, class T>
void s21::map<Key, T>::swap(s21::map<Key, T> &other) noexcept {
  typename BaseTree<Key, T>::Node *temp = this->root_;
  BaseTree<Key, T>::root_ = other.BaseTree<Key, T>::root_;
  other.BaseTree<Key, T>::root_ = temp;
}

template <class Key, class T>
void s21::map<Key, T>::merge(s21::map<Key, T> &other) {  // ЭТО ПОСЛЕ ИТЕРАТОРОВ
  map<Key, T> copy_other(other);
  for (auto it = copy_other.begin(); it != copy_other.end(); ++it) {
    if (BaseTree<Key, T>::SearchNode(BaseTree<Key, T>::root_, (*it).first) ==
        nullptr) {
      // std::cout << (*it).first << std::endl;
      insert((*it));
      other.BaseTree<Key, T>::DeleteNode(other.BaseTree<Key, T>::root_,
                                         (*it).first);
    }
  }
}

/*
Map Iterators
*/

template <class Key, class T>
typename s21::map<Key, T>::iterator s21::map<Key, T>::begin() {
  return iterator(BaseTree<Key, T>::GetMin(BaseTree<Key, T>::root_), nullptr);
}

template <class Key, class T>
typename s21::map<Key, T>::iterator s21::map<Key, T>::end() {
  if (BaseTree<Key, T>::root_ == nullptr) {
    return begin();
  }
  return iterator(nullptr, BaseTree<Key, T>::GetMax(BaseTree<Key, T>::root_));
}

// Map Capasity
template <class Key, class T>
bool s21::map<Key, T>::empty() const noexcept {
  if (BaseTree<Key, T>::root_ == nullptr) return true;
  return false;
}

template <class Key, class T>
size_t s21::map<Key, T>::size() noexcept {
  return s21::BaseTree<Key, T>::GetSize(BaseTree<Key, T>::root_);
}

template <class Key, class T>
size_t s21::map<Key, T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename BaseTree<Key, T>::Node) / 2;
}

// Map Lookup
template <class Key, class T>
bool s21::map<Key, T>::contains(const Key &key) const {
  if (BaseTree<Key, T>::SearchNode(BaseTree<Key, T>::root_, key) != nullptr) {
    return true;
  }
  return false;
}

template <class Key, class T>
template <typename... Args>
std::vector<std::pair<typename s21::map<Key, T>::iterator, bool>>
s21::map<Key, T>::insert_many(Args &&...args) {
  map<Key, T> other{args...};
  std::vector<std::pair<typename s21::map<Key, T>::iterator, bool>> result;
  for (auto it = other.begin(); it != other.end(); ++it) {
    result.push_back(insert(*it));
  }
  return result;
}