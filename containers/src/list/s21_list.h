#ifndef CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  struct Node;
  class ListIterator;
  class ListIteratorConst;

  using iterator = ListIterator;
  using const_iterator = ListIteratorConst;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  struct Node {
    value_type data;
    Node* prev;
    Node* next;

    Node() : data(0), prev(nullptr), next(nullptr) {}
    Node(T data = T(), Node* next = nullptr, Node* prev = nullptr)
        : data(data), prev(prev), next(next) {}
  };

  list() noexcept : head_(nullptr), tail_(nullptr), size_(0) {
    new_node_ = nullptr;
  }

  list(size_type n) : list() {
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const& item) noexcept : list() {
    for (auto it = item.begin(); it != item.end(); ++it) {
      push_back(*it);
    }
  }

  list(const list& other) : list() { copy(other); }

  list(list&& other) noexcept : list() { splice(begin(), other); }

  ~list() {
    clear();

    delete new_node_;
    new_node_ = nullptr;

    head_ = nullptr;
    tail_ = nullptr;
  }

  list& operator=(const list& other) noexcept {
    copy(other);
    return *this;
  }

  list& operator=(list&& other) noexcept {
    splice(begin(), other);
    return *this;
  }

  const_reference front() const noexcept {
    return (head_ != nullptr) ? head_->data : new_node_->data;
  }

  const_reference back() const noexcept {
    return (tail_ != nullptr) ? tail_->data : new_node_->data;
  }

  iterator begin() noexcept { return iterator(head_, nullptr); }

  const_iterator begin() const noexcept {
    return const_iterator(head_, nullptr);
  }

  iterator end() noexcept { return iterator(nullptr, tail_); }

  const_iterator end() const noexcept {
    return const_iterator(new_node_, tail_);
  }

  size_type size() const noexcept { return size_; }

  bool empty() { return size_ ? false : true; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 12;
  }

  reference operator[](size_type index) { return head_[index]; }

  void clear() noexcept {
    while (head_ != nullptr) {
      Node* temp = head_;
      head_ = head_->next;
      delete temp;
    }
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
  }

  iterator insert(iterator index, const_reference data) {
    if (index == begin()) {
      push_front(data);
      return begin();
    } else if (index == end()) {
      push_back(data);
      auto tmp = end();
      --tmp;
      return tmp;
    } else {
      Node* node_pos = new Node{data, index.node(), index.node()->prev};
      index.node()->prev->next = node_pos;
      index.node()->prev = node_pos;
      size_++;
      return iterator(node_pos, nullptr);
    }
  }

  void erase(iterator index) {
    Node* node = get_allocator(index);
    if (node == nullptr) {
      return;
    }
    if (node->prev == nullptr) {
      pop_front();
    } else if (node->next == nullptr) {
      pop_back();
    } else {
      node->prev->next = node->next;
      node->next->prev = node->prev;

      delete node;
    }
  }

  void push_front(const_reference data) {
    Node* node = new Node(data);
    node->next = head_;
    node->prev = nullptr;
    if (head_ != nullptr) head_->prev = node;
    head_ = node;
    if (tail_ == nullptr) tail_ = node;
    ++size_;
  }

  void push_back(const_reference data) {
    Node* node = new Node(data);
    node->prev = tail_;
    node->next = nullptr;
    if (head_ == nullptr) head_ = node;
    if (tail_ != nullptr) tail_->next = node;
    tail_ = node;
    ++size_;
  }

  void pop_front() {
    if (head_ == nullptr) return;
    Node* node = head_;
    head_ = head_->next;
    if (head_)
      head_->prev = nullptr;
    else
      tail_ = nullptr;

    delete node;
    --size_;
  }

  void pop_back() {
    if (tail_ == nullptr) return;
    Node* node = tail_;
    tail_ = tail_->prev;
    if (tail_)
      tail_->next = nullptr;
    else
      head_ = nullptr;

    delete node;
    --size_;
  }

  void swap(list& other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  void merge(list& other) {
    iterator itThis = begin();
    iterator itOther = other.begin();

    while (itOther != other.end()) {
      if (itThis == end() || *itOther < *itThis) {
        insert(itThis, *itOther++);
      } else {
        ++itThis;
      }
    }
    other.clear();
  }

  void sort() {
    if (size_ > 1) {
      for (auto i = begin(); i != end(); ++i) {
        for (auto j = begin(); j != end(); ++j) {
          if (*i < *j) {
            T temp = *i;
            *i = *j;
            *j = temp;
          }
        }
      }
    }
  }

  void splice(iterator index, list& other) {
    if (this != &other) {
      for (auto itr = other.begin(); itr != other.end(); ++itr)
        insert(index, *itr);
      other.clear();
    }
  }

  void reverse() {
    if (size_ <= 1) {
      return;
    }
    Node* current = head_;
    Node* next = nullptr;
    Node* prev = nullptr;

    tail_ = head_;

    while (current != nullptr) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }

    head_ = prev;
  }

  void unique() {
    auto iterator = begin();
    while (iterator != end()) {
      auto it_next = iterator;
      if (++it_next != end() && *iterator == *it_next) {
        erase(it_next);
        --size_;
      } else
        ++iterator;
    }
  }

  void copy(const list& other) {
    if (other.size_ != 0) {
      for (const_iterator it = other.begin(); it != other.end(); ++it) {
        push_back(*it);
      }
    }
  }

  Node* get_allocator(iterator index) { return index.node(); }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    for (const auto& arg : {args...}) {
      insert(pos, arg);
    }
    return pos;
  }

  template <class... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& arg : {args...}) {
      push_back(arg);
    }
  }

  template <class... Args>
  void insert_many_front(Args&&... args) {
    for (const auto& arg : {args...}) {
      push_front(arg);
    }
  }

  class ListIterator {
   protected:
    Node* node_;
    Node* prev_node_;

   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = list::value_type;
    using pointer = value_type*;
    using reference = value_type&;

    ListIterator() : node_(nullptr), prev_node_(nullptr) {}
    ListIterator(Node* node, Node* prev_node)
        : node_(node), prev_node_(prev_node) {}

    bool operator==(const iterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const iterator& other) const {
      return node_ != other.node_ && other.prev_node_ != prev_node_;
    }

    reference operator*() const {
      if (node_ == nullptr) {
        static value_type result;
        return result;
      }
      return node_->data;
    }

    T* operator->() const { return &node_->data; }

    iterator& operator++() {
      if (node_ == nullptr) {
        while (prev_node_ != nullptr) {
          node_ = prev_node_;
          prev_node_ = prev_node_->prev;
        }
        prev_node_ = nullptr;
      } else {
        node_ = node_->next;
      }
      return *this;
    }

    iterator operator++(int) {
      iterator temp(*this);
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      if (node_ == nullptr) {
        node_ = prev_node_;
        prev_node_ = prev_node_->prev;
      } else
        node_ = node_->prev;
      return *this;
    }

    iterator operator--(int) {
      iterator temp(*this);
      --(*this);
      return temp;
    }

    iterator& operator+=(difference_type n) {
      while (n > 0) {
        ++(*this);
        --n;
      }
      while (n < 0) {
        --(*this);
        ++n;
      }
      return *this;
    }

    iterator operator+(difference_type n) const {
      iterator temp(*this);
      return temp += n;
    }

    iterator& operator-=(difference_type n) { return (*this) += -n; }

    iterator operator-(difference_type n) const {
      iterator temp(*this);
      return temp -= n;
    }

    difference_type operator-(const iterator& other) const {
      difference_type count = 0;
      iterator temp(*this);
      while (temp != other) {
        --temp;
        ++count;
      }
      return count;
    }

    T& operator[](difference_type n) const {
      iterator temp(*this);
      temp += n;
      return *temp;
    }

    Node* node() const { return node_; }
  };

  class ListIteratorConst : public ListIterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = list::value_type;
    using pointer = const value_type*;
    using reference = const value_type&;

   public:
    ListIteratorConst(Node* node, Node* tail) : ListIterator(node, tail) {}
    const_reference operator*() const { return (this->node_)->data; }
  };

 private:
  Node* head_;
  Node* tail_;
  size_type size_;
  Node* new_node_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_
