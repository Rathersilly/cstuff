#include <iostream>
#include <vector>
using std::cout, std::endl;

template <typename T> class BinarySearchTree {

  struct Node {
    T data;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
  };

public:
  void print_header() {
    cout << "---header---" << endl;
    if (root())
      cout << "root: " << root()->data;
    if (m_header->left)
      cout << "left: " << m_header->left->data;
    if (m_header->right)
      cout << "right: " << m_header->right->data;
    cout << endl;
  }
  BinarySearchTree() : m_header{new Node} {}
  ~BinarySearchTree() { destroy(root()); }
  void destroy(Node *ptr) {
    if (!ptr)
      return;
    destroy(ptr->left);
    destroy(ptr->right);
    delete ptr;
  }
  BinarySearchTree(const BinarySearchTree &other) {
    m_header = new Node(0);
    m_header->parent = copy(other.root(), m_header);
  }
  Node *copy(const Node *other, Node *parent_node = nullptr) {
    if (!other)
      return nullptr;
    Node *n = new Node(other->data);
    n->parent = parent_node;
    n->left = copy(other->left, n);
    n->right = copy(other->right, n);
    return n;
  }
  BinarySearchTree &operator=(const BinarySearchTree &other) {
    std::cerr << __PRETTY_FUNCTION__ << endl;
    if (other.root() == root())
      return *this;
    destroy(m_header->parent);
    m_header->parent = copy(other.root(), m_header);
    return *this;
  }

  void insert(T n);
  bool find(T n);
  T min() {
    Node *ptr = root();
    while (ptr->left)
      ptr = ptr->left;
    return ptr->data;
  }
  T max() {
    Node *ptr = root();
    while (ptr->right)
      ptr = ptr->right;
    return ptr->data;
  }
  T min2() { return m_header->left->data; }
  T max2() { return m_header->right->data; }

  bool isEmpty();
  void createTree();
  void preorder();
  std::vector<T> inorder();
  void postorder();
  void levelOrder();
  int height();
  void nrecPreorder();
  void nrecInorder();
  void nrecPostorder();
  void display();
  void nrec_preorder();
  void nrec_inorder();
  // void nrec_postorder();
  void nrec_postorder_two_stack();
  void levelorder();

private:
  Node *m_header;
  Node *root() const { return m_header->parent; }
  void preorder(Node *ptr);
  // std::vector<T> inorder(Node *ptr);
  void inorder(Node *node, std::vector<T> &result);
  void postorder(Node *ptr);
  int height(Node *ptr);
  void display(Node *ptr, int level);
};

template <typename T> void BinarySearchTree<T>::insert(T n) {
  Node *ptr = root();
  if (!ptr) {
    ptr = new Node{n};
    m_header->parent = ptr;
    m_header->left = ptr;
    m_header->right = ptr;
    return;
  }

  Node *new_node = new Node{n};
  bool min_flag = true;
  bool max_flag = true;

  while (ptr) {
    if (n < ptr->data) {
      max_flag = false;
      if (ptr->left)
        ptr = ptr->left;
      else {
        ptr->left = new_node;
        if (min_flag)
          m_header->left = new_node;
        return;
      }
    }
    if (n > ptr->data) {
      min_flag = false;
      if (ptr->right)
        ptr = ptr->right;
      else {
        ptr->right = new_node;
        if (max_flag)
          m_header->right = new_node;
        return;
      }
    }
  }
  // should never get here
  insert(false);
}

template <typename T> bool BinarySearchTree<T>::find(T n) {

  Node *ptr = root();

  if (!ptr)
    return false;
  while (ptr) {
    if (n == ptr->data)
      return true;
    if (n < ptr->data)
      ptr = ptr->left;
    else
      ptr = ptr->right;
  }
  return false;
}

template <typename T> std::vector<T> BinarySearchTree<T>::inorder() {
  std::vector<T> result;
  cout << '\n';
  inorder(root(), result);
  return result;
}
template <typename T>
void BinarySearchTree<T>::inorder(Node *node, std::vector<T> &result) {
  if (!node)
    return;
  inorder(node->left, result);
  result.push_back(node->data);
  std::cerr << node->data << std::flush;
  inorder(node->right, result);
}
