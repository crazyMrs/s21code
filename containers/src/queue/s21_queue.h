#ifndef CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <typename T>
class queue {
 public:
  class QueueIterator;
  class QueueIteratorConst;

  using iterator = QueueIterator;
  using const_iterator = QueueIteratorConst;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  struct Node {
    T data;
    Node* next;

    Node() : data(0), next(nullptr) {}
    Node(T data = T(), Node* next = nullptr) : data(data), next(next) {}
  };

  queue() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

  queue(std::initializer_list<value_type> items) : queue() {
    for (auto it = items.begin(); it != items.end(); ++it) {
      push(*it);
    }
  }

  queue(const queue& q) : queue() { my_copy(q); }

  queue(queue&& q) noexcept : queue() { my_swap(q); }

  ~queue() {
    my_clear();
    head_ = nullptr;
    tail_ = nullptr;
  }

  queue& operator=(queue&& q) noexcept {
    my_swap(q);
    return *this;
  }

  queue& operator=(const queue& other) noexcept {
    my_copy(other);
    return *this;
  }

  const_reference front() const {
    if (my_empty()) {
      throw std::out_of_range("Error: queue is empty");
    }
    return head_->data;
  }

  const_reference back() const {
    if (my_empty()) {
      throw std::out_of_range("Error: queue is empty");
    }
    return tail_->data;
  }

  iterator begin() noexcept { return iterator(head_); }

  const_iterator begin() const noexcept { return const_iterator(head_); }

  iterator end() noexcept { return iterator(nullptr); }

  const_iterator end() const noexcept { return const_iterator(nullptr); }

  const_iterator cbegin() const { return const_iterator(head_); }

  const_iterator cend() const { return const_iterator(nullptr); }

  size_t my_size() const noexcept { return size_; }

  bool my_empty() const { return size_ == 0; }

  void my_swap(queue& other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  void pop() {
    if (head_) {
      Node* node = head_->next;
      delete head_;
      head_ = node;
      --size_;
      if (size_ > 2) tail_ = node;
    }
  }

  void push(const_reference data) {
    Node* node = new Node(data);
    if (!head_)
      head_ = node;
    else
      tail_->next = node;
    tail_ = node;
    ++size_;
  }

  void my_clear() {
    while (!my_empty()) {
      pop();
    }
  }

  void my_copy(const queue& other) {
    my_clear();
    Node* node = other.head_;
    while (node) {
      push(node->data);
      node = node->next;
    }
  }

  template <class... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& arg : {args...}) {
      push(arg);
    }
  }

  class QueueIterator {
   public:
    QueueIterator() : node_(nullptr) {}

    explicit QueueIterator(Node* node) : node_(node) {}

    reference operator*() const { return node_->data; }

    iterator& operator++() {
      node_ = node_->next;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const iterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const iterator& other) const {
      return node_ != other.node_;
    }

   private:
    Node* node_;
  };

  class QueueIteratorConst : public QueueIterator {
    using pointer = const value_type*;
    using reference = const value_type&;

   public:
    QueueIteratorConst() : node_(nullptr) {}

    explicit QueueIteratorConst(Node* node) : node_(node) {}

    const_reference operator*() const { return node_->data; }

    QueueIteratorConst& operator++() {
      if (node_) {
        node_ = node_->next;
      }
      return *this;
    }

    QueueIteratorConst operator++(int) {
      QueueIteratorConst temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const QueueIteratorConst& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const QueueIteratorConst& other) const {
      return node_ != other.node_;
    }

   private:
    const Node* node_;
  };

 private:
  Node* head_;
  Node* tail_;
  size_t size_;
};
};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_