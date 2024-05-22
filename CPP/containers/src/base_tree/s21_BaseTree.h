#ifndef CPP2_S21_CONTAINERS_SRC_BASETREE_S21_BASETREE_H_
#define CPP2_S21_CONTAINERS_SRC_BASETREE_S21_BASETREE_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <class Key, class T>
class BaseTree {
 public:
  class BaseTreeIterator;
  class BaseTreeConstIterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = BaseTreeIterator;
  using const_iterator = const BaseTreeConstIterator;
  using size_type = size_t;

 protected:
  class Node {
   public:
    Node(value_type v);
    Node(value_type v, Node* n);
    int height_ = -1;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    value_type value_;
    Node* parent_ = nullptr;
  };
  Node* root_;

 public:
  BaseTree();

 protected:
  Node* CopyTree(Node** node, Node* parent);
  void FreeNode(Node* node);

  // Методы AVLTree
  int GetHeight(Node* node);
  void SetHeight(Node* node);
  int GetBalance(Node* node);
  void SetBalance(Node* node);
  void RightRotate(Node* node);
  void LeftRotate(Node* node);
  void Swap(Node* first, Node* second);
  Node* AddNode(Node* node, const value_type& value);
  Node* DeleteNode(Node* node, const key_type& key);
  Node* SearchNode(Node* node, const key_type& key);
  size_type GetSize(Node* node);
  static Node* GetMin(Node* node);
  static Node* GetMax(Node* node);

 public:
  class BaseTreeIterator {
   protected:
    Node* node_;
    Node* prev_node_;

   public:
    BaseTreeIterator();
    BaseTreeIterator(Node* node, Node* prev_node);
    value_type& operator*();
    BaseTreeIterator& operator++();
    BaseTreeIterator operator++(int);
    BaseTreeIterator& operator--();
    BaseTreeIterator operator--(int);
    bool operator!=(const BaseTreeIterator& value);
    bool operator==(const BaseTreeIterator& value);
  };

  class BaseTreeConstIterator : public BaseTreeIterator {
   public:
    const value_type& operator*();
  };
};
}  // namespace s21

#include "s21_BaseTree.cc"
#endif  // CPP2_S21_CONTAINERS_SRC_BASETREE_S21_BASETREE_H_
