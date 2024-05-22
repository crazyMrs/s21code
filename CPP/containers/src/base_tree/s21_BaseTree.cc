#include "s21_BaseTree.h"

/*
Конструктор для Node
*/
namespace s21 {

template <class Key, class T>
BaseTree<Key, T>::Node::Node(value_type v) : value_(v) {}

template <class Key, class T>
BaseTree<Key, T>::Node::Node(value_type v, Node *n) : value_(v), parent_(n) {}

/*
Дополнительные функции для для Node
*/

template <class Key, class T>
typename BaseTree<Key, T>::Node *BaseTree<Key, T>::CopyTree(
    BaseTree<Key, T>::Node **node, BaseTree<Key, T>::Node *parent) {
  if (parent == nullptr) return nullptr;
  *node = new Node(parent->value_);
  (*node)->left_ = CopyTree(&((*node)->left_), parent->left_);
  (*node)->right_ = CopyTree(&((*node)->right_), parent->right_);
  if ((*node)->left_ != nullptr) (*node)->left_->parent_ = *node;
  if ((*node)->right_ != nullptr) (*node)->right_->parent_ = *node;
  return *node;
}

template <class Key, class T>
void BaseTree<Key, T>::FreeNode(BaseTree<Key, T>::Node *node) {
  if (node == nullptr) return;
  FreeNode(node->left_);
  FreeNode(node->right_);
  delete node;
}

template <class Key, class T>
int BaseTree<Key, T>::GetHeight(BaseTree<Key, T>::Node *node) {
  return node == nullptr ? -1 : node->height_;
}

template <class Key, class T>
void BaseTree<Key, T>::SetHeight(BaseTree<Key, T>::Node *node) {
  int max = GetHeight(node->left_) < GetHeight(node->right_)
                ? GetHeight(node->right_)
                : GetHeight(node->left_);
  node->height_ = max + 1;
}

template <class Key, class T>
void BaseTree<Key, T>::SetBalance(BaseTree<Key, T>::Node *node) {
  int balance = GetBalance(node);
  // std::cout << node->value_.first << " BALANCE: " << balance << std::endl;
  if (balance == -2) {
    if (GetBalance(node->left_) == 1) LeftRotate(node->left_);
    RightRotate(node);
  } else if (balance == 2) {
    if (GetBalance(node->right_) == -1) RightRotate(node->right_);
    LeftRotate(node);
  }
}

template <class Key, class T>
int BaseTree<Key, T>::GetBalance(BaseTree<Key, T>::Node *node) {
  return node == nullptr ? 0 : GetHeight(node->right_) - GetHeight(node->left_);
}

template <class Key, class T>
void BaseTree<Key, T>::LeftRotate(BaseTree<Key, T>::Node *node) {
  Swap(node, node->right_);
  Node *buffer = node->left_;
  node->left_ = node->right_;
  if (node->left_ != nullptr) node->left_->parent_ = node;
  node->right_ = node->left_->right_;
  if (node->right_ != nullptr) node->right_->parent_ = node;
  node->left_->right_ = node->left_->left_;
  if (node->left_->right_ != nullptr)
    node->left_->right_->parent_ = node->left_;
  node->left_->left_ = buffer;
  if (node->left_->left_ != nullptr) node->left_->left_->parent_ = node->left_;
  SetHeight(node->left_);
  SetHeight(node);
}

template <class Key, class T>
void BaseTree<Key, T>::RightRotate(BaseTree<Key, T>::Node *node) {
  Swap(node, node->left_);
  Node *buffer = node->right_;
  node->right_ = node->left_;
  if (node->right_ != nullptr) node->right_->parent_ = node;
  node->left_ = node->right_->left_;
  if (node->left_ != nullptr) node->left_->parent_ = node;
  node->right_->left_ = node->right_->right_;
  if (node->right_->left_ != nullptr)
    node->right_->left_->parent_ = node->right_;
  node->right_->right_ = buffer;
  if (node->right_->right_ != nullptr)
    node->right_->right_->parent_ = node->right_;
  SetHeight(node->right_);
  SetHeight(node);
}

template <class Key, class T>
void BaseTree<Key, T>::Swap(BaseTree<Key, T>::Node *first,
                            BaseTree<Key, T>::Node *second) {
  value_type copy = first->value_;
  first->value_.~value_type();
  new (&first->value_) value_type(second->value_.first, second->value_.second);
  second->value_.~value_type();
  new (&second->value_) value_type(copy.first, copy.second);
}

template <class Key, class T>
typename BaseTree<Key, T>::Node *BaseTree<Key, T>::AddNode(
    Node *node, const value_type &value) {
  if (root_ == nullptr) {
    node = root_ = new Node(value, nullptr);
    return node;
  }
  if (value < node->value_) {
    if (node->left_ == nullptr) {
      node->left_ = new Node(value, node);
      SetHeight(node->left_);
    } else {
      AddNode(node->left_, value);
    }
  } else if (value > node->value_) {
    if (node->right_ == nullptr) {
      node->right_ = new Node(value, node);
      SetHeight(node->right_);
    } else {
      AddNode(node->right_, value);
    }
  } else if (value == node->value_) {
    Node *temp = new Node(value, node);
    Node *copy_right = node->right_;
    node->right_ = temp;
    temp->right_ = copy_right;
    SetHeight(node->right_);
  }

  SetHeight(node);
  SetBalance(node);

  return node;
}

template <class Key, class T>
typename BaseTree<Key, T>::Node *BaseTree<Key, T>::SearchNode(
    BaseTree<Key, T>::Node *node, const key_type &key) {
  if (node == nullptr) return nullptr;
  if (node->value_.first == key) return node;
  return (node->value_.first > key ? SearchNode(node->left_, key)
                                   : SearchNode(node->right_, key));
}

template <class Key, class T>
typename BaseTree<Key, T>::Node *BaseTree<Key, T>::GetMin(
    BaseTree<Key, T>::Node *node) {
  if (node == nullptr) return nullptr;
  if (node->left_ == nullptr) return node;
  return GetMin(node->left_);
}

template <class Key, class T>
typename BaseTree<Key, T>::Node *BaseTree<Key, T>::GetMax(
    BaseTree<Key, T>::Node *node) {
  if (node == nullptr) return nullptr;
  if (node->right_ == nullptr) return node;
  return GetMax(node->right_);
}

template <class Key, class T>
size_t BaseTree<Key, T>::GetSize(BaseTree<Key, T>::Node *node) {
  size_type size = 0;
  if (node == nullptr)
    return 0;
  else
    size += 1;
  size += GetSize(node->left_);
  size += GetSize(node->right_);
  return size;
}

template <class Key, class T>
typename BaseTree<Key, T>::Node *BaseTree<Key, T>::DeleteNode(
    BaseTree<Key, T>::Node *node, const key_type &key) {
  if (node == nullptr)
    return nullptr;
  else if (key < node->value_.first) {
    node->left_ = DeleteNode(node->left_, key);
  } else if (key > node->value_.first) {
    node->right_ = DeleteNode(node->right_, key);
  } else if (node->left_ == nullptr || node->right_ == nullptr) {
    Node *new_node = (node->left_ == nullptr) ? node->right_ : node->left_;
    if (new_node != nullptr) {
      new_node->parent_ = node->parent_;
    }
    if (node == root_) root_ = new_node;
    delete node;
    node = new_node;
  } else {
    Node *maxInleft_ = GetMax(node->left_);  //максимум слева
    node->value_.~value_type();
    new (&node->value_)
        value_type(maxInleft_->value_.first, maxInleft_->value_.second);
    node->left_ = DeleteNode(node->left_, maxInleft_->value_.first);
  }
  if (node != nullptr) {
    SetHeight(node);
    SetBalance(node);
  }
  return node;
}

template <class Key, class T>
BaseTree<Key, T>::BaseTree() : root_(nullptr) {}

// Конструкторы для итераторов
template <class Key, class T>
BaseTree<Key, T>::BaseTreeIterator::BaseTreeIterator()
    : node_(nullptr), prev_node_(nullptr) {}

template <class Key, class T>
BaseTree<Key, T>::BaseTreeIterator::BaseTreeIterator(Node *node,
                                                     Node *prev_node)
    : node_(node), prev_node_(prev_node) {}

// Методы итераторов
template <class Key, class T>
inline std::pair<const Key, T>
    &BaseTree<Key, T>::BaseTreeIterator::operator*() {
  if (node_ == nullptr) {
    static value_type value;
    return value;
  }
  return node_->value_;
}

template <class Key, class T>
inline const std::pair<const Key, T>
    &BaseTree<Key, T>::BaseTreeConstIterator::operator*() {
  return BaseTreeIterator::operator*();
}

template <class Key, class T>
typename BaseTree<Key, T>::BaseTreeIterator &
BaseTree<Key, T>::BaseTreeIterator::operator++() {
  if (node_ == nullptr) {
    node_ = prev_node_;
    if (node_ != nullptr) prev_node_ = node_->parent_;
    return *this;
  }
  if (node_->right_ != nullptr) {
    node_ = GetMin(node_->right_);
    prev_node_ = node_->parent_;
  } else {
    Node *temp = node_;  // null
    while (node_->parent_ != nullptr && node_ == node_->parent_->right_) {
      prev_node_ = node_;
      node_ = node_->parent_;
    }
    prev_node_ = node_;
    node_ = node_->parent_;
    if (node_ == nullptr) {
      prev_node_ = temp;
    }
  }
  return *this;
}

template <class Key, class T>
typename BaseTree<Key, T>::BaseTreeIterator &
BaseTree<Key, T>::BaseTreeIterator::operator--() {
  if (node_ == nullptr) {
    node_ = prev_node_;
    prev_node_ = nullptr;
    return *this;
  }
  if (node_->left_ != nullptr) {
    node_ = GetMax(node_->left_);
    prev_node_ = node_->left_;
  } else {
    while (node_->parent_ != nullptr && node_ == node_->parent_->left_) {
      prev_node_ = node_;
      node_ = node_->parent_;
    }
    prev_node_ = node_;
    node_ = node_->parent_;
    if (node_ == nullptr) {
      prev_node_ = GetMax(prev_node_);
    };
  }
  return *this;
}

template <class Key, class T>
typename BaseTree<Key, T>::BaseTreeIterator
BaseTree<Key, T>::BaseTreeIterator::operator++(int) {
  BaseTreeIterator *last_node = this;
  ++(*this);
  return *last_node;
}

template <class Key, class T>
typename BaseTree<Key, T>::BaseTreeIterator
BaseTree<Key, T>::BaseTreeIterator::operator--(int) {
  BaseTreeIterator *last_node = this;
  --(*this);
  return *last_node;
}

template <class Key, class T>
bool BaseTree<Key, T>::BaseTreeIterator::operator!=(
    const BaseTree<Key, T>::BaseTreeIterator &value) {
  return node_ != value.node_;
}

template <class Key, class T>
bool BaseTree<Key, T>::BaseTreeIterator::operator==(
    const BaseTree<Key, T>::BaseTreeIterator &value) {
  return node_ == value.node_;
}
};  // namespace s21