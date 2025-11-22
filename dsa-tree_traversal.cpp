#include <cstring>
#include <iostream>
#include <queue>
#include <ranges>
#include <stack>
#include <string>
using namespace std;
// TODO: display() to confirm in/pre creation works
// then do in/post creation
class BinaryTree {

public:
  struct Node {
    char data;
    Node *left = nullptr;
    Node *right = nullptr;
  };

public:
  BinaryTree() : root{nullptr} {}
  ~BinaryTree() { destroy(root); }
  bool isEmpty();
  void createTree();
  void preorder();
  void inorder();
  void postorder();
  void levelOrder();
  int height();
  void nrecPreorder();
  void nrecInorder();
  void nrec_preorder();
  void nrec_inorder();
  // void nrec_postorder();
  void nrec_postorder_two_stack();
  void levelorder();

  void create_tree_inpre(char *in, char *pre);
  void create_tree_inpost(char *in, char *post);

private:
  Node *root;
  void preorder(Node *ptr);
  void inorder(Node *ptr);
  void postorder(Node *ptr);
  int height(Node *ptr);
  void display(Node *ptr, int level);
  Node *create_tree_inpre(char *in, char *pre, int num);   // implementation
  Node *create_tree_inpost(char *in, char *post, int num); // implementation

  void destroy(Node *);
};

void BinaryTree::createTree() {
  destroy(root);
  // Srivistava pg 519
  root = new Node('A');
  root->left = new Node('B');
  root->right = new Node('C');
  root->left->left = new Node('D');
  root->left->right = new Node('E');
  root->right->left = new Node('F');
  root->right->right = new Node('G');

  root->left->left->right = new Node('H');
  root->right->left->left = new Node('I');
  root->right->right->left = new Node('J');
  root->right->right->right = new Node('K');
} // End of createTree(

void BinaryTree::preorder() {
  preorder(root);
  cout << '\n';
}

void BinaryTree::inorder() {
  inorder(root);
  cout << '\n';
}

void BinaryTree::postorder() {
  postorder(root);
  cout << '\n';
}

// in recursive traversive, the function is its own breadcrumb
void BinaryTree::preorder(Node *node) {
  if (!node)
    return;
  cout << node->data;
  preorder(node->left);
  preorder(node->right);
}

void BinaryTree::inorder(Node *node) {
  if (!node)
    return;
  inorder(node->left);
  cout << node->data;
  inorder(node->right);
}

void BinaryTree::postorder(Node *node) {
  if (!node)
    return;
  postorder(node->left);
  postorder(node->right);
  cout << node->data;
}
void BinaryTree::nrec_preorder() {
  Node *ptr = root;
  std::stack<Node *> s;

  if (ptr) {
    s.push(ptr);
    while (!s.empty()) {
      ptr = s.top();
      s.pop();
      cout << ptr->data << " ";
      if (ptr->right)
        s.push(ptr->right);
      if (ptr->left)
        s.push(ptr->left);
    }
    cout << '\n';
  } else
    cout << "tree is empty\n";
}
void BinaryTree::nrec_inorder() {
  Node *ptr = root;
  std::stack<Node *> s;

  if (!ptr) {
    cout << "tree is empty\n";
    return;
  }

  // 1. Traverse to the leftmost node, pushing parents onto the stack
  while (ptr || !s.empty()) {
    // Go as far left as possible, pushing nodes onto the stack
    // (leaving breadcrumbs)
    while (ptr) {
      s.push(ptr);
      ptr = ptr->left;
    }

    // We've hit a null left pointer, so pop the parent node
    // go to prev breadcrumb
    // note we never pushed the null (past the end) ptr to the stack
    ptr = s.top();
    s.pop();

    // 2. Visit the current node (V)
    cout << ptr->data << " ";

    // 3. Move right JUST ONCE and repeat, going down left tree
    ptr = ptr->right;
  }

  cout << '\n';
}

void BinaryTree::nrec_postorder_two_stack() {
  cout << __PRETTY_FUNCTION__ << endl;
  Node *ptr = root;

  if (!ptr) {
    cout << "tree is empty\n";
    return;
  }

  std::stack<Node *> s1; // Main processing stack
  std::stack<Node *> s2; // Output stack

  s1.push(ptr);

  // Phase 1: Reversing the order
  while (!s1.empty()) {
    ptr = s1.top();
    s1.pop();

    // NOTE: visiting right here gives us NRL Traversal
    // - compare this to preorder
    // cout << ptr->data;

    // Push the node onto the output stack
    s2.push(ptr);

    // Crucial Order: Push left then right (L-R) to s1
    // This ensures when s2 is read, the children were processed before the
    // parent.
    if (ptr->left)
      s1.push(ptr->left);
    if (ptr->right)
      s1.push(ptr->right);
  }

  // Phase 2 : Printing the reversed order
  while (!s2.empty()) {
    cout << s2.top()->data << " ";
    s2.pop();
  }

  cout << '\n';
}

void BinaryTree::levelorder() {
  Node *ptr = root;

  if (!ptr) {
    cout << "tree is empty\n";
    return;
  }

  // Use a queue for Level Order Traversal (BFS)
  std::queue<Node *> q;

  // Start by pushing the root
  q.push(ptr);

  // Continue as long as there are nodes in the queue
  while (!q.empty()) {
    // 1. Visit (Dequeue) the node at the front
    ptr = q.front();
    q.pop();

    cout << ptr->data;

    // 2. Enqueue the children (from left to right)
    // This ensures children are processed in the next level, maintaining order.
    if (ptr->left) {
      q.push(ptr->left);
    }
    if (ptr->right) {
      q.push(ptr->right);
    }
  }

  cout << '\n';
}
void BinaryTree::destroy(Node *ptr) {
  if (!ptr)
    return;
  destroy(ptr->left);
  destroy(ptr->right);
  delete ptr;
}

void BinaryTree::create_tree_inpre(char *in, char *pre) {
  destroy(root);
  root = create_tree_inpre(in, pre, strlen(in));
}
BinaryTree::Node *BinaryTree::create_tree_inpre(char *in, char *pre, int num) {
  Node *temp;
  char *q;
  if (num == 0)
    return nullptr;
  temp = new Node(pre[0]);
  if (num == 1)
    return temp;
  q = in;
  int i;
  for (i = 0; q[0] != pre[0]; ++i) {
    ++q;
  }
  // Now q points to root of in,
  // and i is the number of nodes in its left subtree

  // Left subtree:
  temp->left = create_tree_inpre(in, pre + 1, i);
  // Left subtree:
  int j;
  for (j = 0; j <= i + 1; ++j)
    ++pre;
  temp->right = create_tree_inpre(q + 1, pre, num - i - 1);
  return temp;
}
void BinaryTree::create_tree_inpost(char *in, char *post) {}

int main() {
  BinaryTree tree;
  tree.createTree();
  tree.preorder();  // ABDHECFIGJK
  tree.inorder();   // DHBEAIFCJGK
  tree.postorder(); // HDEBIFJKGCA
  tree.nrec_preorder();
  tree.nrec_inorder();
  tree.nrec_postorder_two_stack();
  tree.levelorder(); // ABCDEFGHIJK

  // sriv p 537 - creation of trees from strings
  string inorder_string = " ABDHECFIGJK";
  string preorder_string = "DHBEAIFCJGK";

  string inorder_string2 = "HIDJEBKFGCA";
  string post_order_string2 = "HDIBEJAKFCG";
}
