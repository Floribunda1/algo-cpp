#include <iostream>

class AVLTreeNode {
public:
  int el;
  int height;
  AVLTreeNode *left = nullptr;
  AVLTreeNode *right = nullptr;

  explicit AVLTreeNode(int val) : el{val}, height{0} {};
};

class AVLTree {
private:
  AVLTreeNode *root = nullptr;

  AVLTreeNode *FindMinNode_(AVLTreeNode *t) {
    if (t == nullptr) return nullptr;
    if (t->left == nullptr) return t;
    return FindMinNode_(t->left);
  }

  AVLTreeNode *FindMaxNode_(AVLTreeNode *t) {
    if (t == nullptr) return nullptr;
    if (t->right == nullptr) return t;
    return FindMaxNode_(t->right);
  }

  void InsertNode_(int val, AVLTreeNode *&t) {
    if (t == nullptr) {
      t = new AVLTreeNode{val};
    } else if (val < t->el) {
      InsertNode_(val, t->left);
    } else if (val > t->el) {
      InsertNode_(val, t->right);
    }
    BalanceTree_(t);
  }

  void RemoveNode_(int val, AVLTreeNode *&t) {
    if (t == nullptr) return;
    if (val < t->el) {
      RemoveNode_(t->el, t->left);
      return;
    }
    if (val > t->el) {
      RemoveNode_(t->el, t->right);
      return;
    }
    // 1. leaf
    if (t->left == nullptr && t->right == nullptr) {
      delete t;
      return;
    }
    // 2. has one child
    if (t->left == nullptr || t->right == nullptr) {
      auto old_node = t;
      t = t->left == nullptr ? t->right : t->left;
      delete old_node;
      return;
    }
    // 3. has two children
    if (t->left != nullptr && t->right != nullptr) {
      t->el = FindMinNode_(t->right)->el;
      RemoveNode_(t->el, t->right);
    }
    BalanceTree_(t);
  }

  void BalanceTree_(AVLTreeNode *&t) {
    if (t == nullptr) return;
    int balance_factor = height_(t->left) - height_(t->right);;
    if (balance_factor > 1) {
      if (height_(t->left->left) >= height_(t->left->right)) {
        RightRotate_(t);
      } else {
        LeftRotate_(t->left);
        RightRotate_(t);
      }
    } else if (balance_factor < -1) {
      if (height_(t->right->right) > height_(t->right->left)) {
        LeftRotate_(t);
      } else {
        RightRotate_(t->right);
        LeftRotate_(t);
      }
    }
    t->height = std::max(height_(t->left), height_(t->right)) + 1;
  }

  void RightRotate_(AVLTreeNode *&r) {
    auto pivot = r->left;
    r->left = pivot->right;
    pivot->right = r;
    r->height = std::max(height_(r->left), height_(r->right)) + 1;
    pivot->height = std::max(height_(pivot->left), height_(pivot->right)) + 1;
    r = pivot;
  }

  void LeftRotate_(AVLTreeNode *&r) {
    auto pivot = r->right;
    r->right = pivot->left;
    pivot->left = r;
    r->height = std::max(height_(r->left), height_(r->right)) + 1;
    pivot->height = std::max(height_(pivot->left), height_(pivot->right)) + 1;
    r = pivot;
  }

  void PrintNode_(AVLTreeNode *t) {
    if (t == nullptr) return;
    PrintNode_(t->left);
    std::cout << t->el << "\n";
    PrintNode_(t->right);
  }

  int height_(AVLTreeNode *t) {
    return t == nullptr ? -1 : t->height;
  }

public:
  explicit AVLTree() = default;

  void Insert(int val) {
    InsertNode_(val, root);
  }

  void Remove(int val) {
    RemoveNode_(val, root);
  }

  void Print() {
    PrintNode_(root);
  };

  int FindMin() {
    auto min_node = FindMinNode_(root);
    if (min_node != nullptr) { return min_node->el; };
  }

  int FindMax() {
    auto max_node = FindMaxNode_(root);
    if (max_node != nullptr) { return max_node->el; };
  }
};

int main() {
  AVLTree tree{};
  tree.Insert(10);
  tree.Insert(29);
  tree.Insert(33);
  tree.Insert(20);

  AVLTree tree2{};
  tree2.Insert(33);
  tree2.Insert(20);
  tree2.Insert(10);

  AVLTree doubleLeftTree{};
  doubleLeftTree.Insert(10);
  doubleLeftTree.Insert(7);
  doubleLeftTree.Insert(11);
  doubleLeftTree.Insert(4);
  doubleLeftTree.Insert(8);
  doubleLeftTree.Insert(9);

  AVLTree doubleRightTree{};
  doubleRightTree.Insert(10);
  doubleRightTree.Insert(7);
  doubleRightTree.Insert(23);
  doubleRightTree.Insert(29);
  doubleRightTree.Insert(20);
  doubleRightTree.Insert(17);

  return 1;
}