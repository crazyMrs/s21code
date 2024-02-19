#ifndef CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_

#include <cstddef>
#include <stdexcept>

namespace s21 {

template <typename T>
class stack {
 public:
  class StackIterator;
  class StackIteratorConst;

  using iterator = StackIterator;
  using const_iterator = StackIteratorConst;
  using reference = T&;
  using const_reference = const T&;

  struct Node {
    T data;
    Node* next;

    Node() : data(0), next(nullptr) {}
    Node(T data = T(), Node* next = nullptr) : data(data), next(next) {}
  };

  stack() noexcept : head_(nullptr), size_(0) {}

  stack(const stack& q) : stack() { Copy(q); }

  stack(stack&& q) noexcept : stack() {
    Swap(q);
    q.Clear();
  }

  ~stack() {
    Clear();
    head_ = nullptr;
  }

  stack& operator=(const stack& other) noexcept {
    if (this != &other) {
      Clear();
      Copy(other);
    }
    return *this;
  }

  iterator begin() noexcept { return iterator(head_); }

  const_iterator begin() const noexcept { return const_iterator(head_); }

  iterator end() noexcept { return iterator(nullptr); }

  const_iterator end() const noexcept { return const_iterator(nullptr); }

  const_iterator cbegin() const { return const_iterator(head_); }

  const_iterator cend() const { return const_iterator(nullptr); }

  const_reference Top() const {
    if (Empty()) {
      throw std::out_of_range("Error: Stack is Empty");
    }
    return head_->data;
  }

  size_t Size() const noexcept { return size_; }

  bool Empty() const { return size_ == 0; }

  void Swap(stack& other) {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
  }

  void Pop() {
    if (Empty()) {
      throw std::out_of_range("Error: Stack is Empty");
    }
    if (head_) {
      Node* node = head_->next;
      delete head_;
      head_ = node;
      size_--;
    }
  }

  void Push(const_reference data) {
    Node* node = new Node(data);
    node->next = head_;
    head_ = node;
    ++size_;
  }

  void Clear() {
    while (!Empty()) {
      Pop();
    }
  }

  void Copy(const stack& other) {
    Clear();
    Node* node = other.head_;
    stack temp_stack;
    while (node) {
      temp_stack.Push(node->data);
      node = node->next;
    }
    while (!temp_stack.Empty()) {
      Push(temp_stack.Top());
      temp_stack.Pop();
    }
  }

  template <class... Args>
  void insert_many_front(Args&&... args) {
    for (const auto& arg : {args...}) {
      Push(arg);
    }
  }

  class StackIterator {
   public:
    StackIterator() : node_(nullptr) {}

    explicit StackIterator(Node* node) : node_(node) {}

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

    bool operator==(const iterator& other) { return node_ == other.node_; }

    bool operator!=(const iterator& other) { return (*this) != other; }

   private:
    Node* node_;
  };

  class StackIteratorConst : public StackIterator {
    using pointer = const T*;
    using reference = const T&;

   public:
    StackIteratorConst() : node_(nullptr) {}

    explicit StackIteratorConst(Node* node) { node_(node); }

    const_reference operator*() const { return node_->data; }

    StackIteratorConst& operator++() {
      if (node_) {
        node_ = node_->next;
      }
      return *this;
    }

    StackIteratorConst operator++(int) {
      StackIteratorConst temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const StackIteratorConst& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const StackIteratorConst& other) const {
      return node_ != other.node_;
    }

   private:
    const Node* node_;
  };

 private:
  Node* head_;  //ссылка на 1 элемент
  size_t size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_