#include <iostream>

template<class T>
class AVLTree {
private:
  class BinaryTreeNode {
  public:
    T el;
    BinaryTreeNode *left = nullptr;
    BinaryTreeNode *right = nullptr;

    explicit BinaryTreeNode(T el) : el{el} {};
  };

  BinaryTreeNode *root = nullptr;

  BinaryTreeNode *clone(BinaryTreeNode *t) const {
    if (t == nullptr) return nullptr;
    auto *new_node = new BinaryTreeNode{t->el};
    new_node->left = clone(t->left);
    new_node->right = clone(t->right);
    return new_node;
  }

  BinaryTreeNode *find_min_node(BinaryTreeNode *node) {
    if (node == nullptr) return nullptr;
    if (node->left == nullptr) return node;

    return find_min_node(node->left);
  }

  BinaryTreeNode *find_max_node(BinaryTreeNode *node) {
    if (node == nullptr) return nullptr;
    if (node->left == nullptr) return node;

    return find_max_node(node->right);
  }

  void insert_node(T &&val, BinaryTreeNode *&node) {
    if (node == nullptr) {
      node = new BinaryTreeNode{std::move(val)};
      return;
    };
    if (val < node->el) {
      insert_node(std::move(val), node->left);
    } else if (val > node->el) {
      insert_node(std::move(val), node->right);
    }
  }

  void print_node(BinaryTreeNode *node) const {
    if (node == nullptr) return;
    print_node(node->left);
    std::cout << node->el << '\n';
    print_node(node->right);
  }

  const BinaryTreeNode *find_node(T &&val, BinaryTreeNode *node) const {
    if (node == nullptr) return nullptr;
    if (val == node->el) return node;
    if (val > node->el) return find_node(std::move(val), node->right);
    if (val < node->el) return find_node(std::move(val), node->left);
    return nullptr;
  }

  void remove_node(T &&val, BinaryTreeNode *&node) {
    if (node == nullptr) return;
    if (val < node->el) {
      remove_node(std::move(val), node->left);
      return;
    };
    if (val > node->el) {
      remove_node(std::move(val), node->right);
      return;
    };
    // two children
    if (node->left && node->right) {
      node->el = find_min_node(node->right)->el;
      remove_node(std::move(node->el), node->right);
      // leaf node
    } else if (node->left == nullptr && node->right == nullptr) {
      delete node;
      node = nullptr;
      // one child
    } else {
      BinaryTreeNode *old_node = node;
      node = node->left != nullptr ? node->left : node->right;
      delete old_node;
    }
  }

  void make_node_empty(BinaryTreeNode *&node) {
    if (node == nullptr) return;
    make_node_empty(node->left);
    make_node_empty(node->right);
    delete node;
    node = nullptr;
  }

public:
  explicit AVLTree() = default;

  // 3
  AVLTree(AVLTree<T> &other) {
    root = clone(other);
  };

  AVLTree<T> &operator=(const AVLTree<T> &other) {
    if (this == &other) return *this;
    root = clone(other);
    return *this;
  };

  ~AVLTree() {
    make_empty();
  };

  // 5
  AVLTree(AVLTree<T> &&other) noexcept {
    root = other.root;
    other.root = nullptr;
  };

  AVLTree<T> &operator=(AVLTree<T> &&other) noexcept {
    if (this == &other) return *this;
    root = other.root;
    other.root = nullptr;
    return *this;
  };

  bool contains(T &&val) const {
    auto node = find_node(std::move(val), root);
    return node != nullptr;
  };

  const T &find_min() const {
    BinaryTreeNode *node = find_min_node(root);
    return node->el;
  };

  const T &find_max() const {
    BinaryTreeNode *node = find_max_node(root);
    return node->el;
  };

  bool is_empty() const {
    return root == nullptr;
  };

  void print() const {
    print_node(root);
  };

  void make_empty() {
    make_node_empty(root);
  };

  void insert(T &&val) {
    insert_node(std::move(val), root);
  }

  void remove(T &&val) {
    remove_node(std::move(val), root);
  };
};

int main() {
  AVLTree<int> tree;
  tree.insert(1);
  tree.insert(3);
  tree.insert(10);
  tree.insert(7);
  tree.insert(9);
  tree.insert(6);
  tree.remove(6);
  std::cout << tree.contains(6) << std::endl;
}