#include <iostream>
#include <queue>
#include <stack>
using namespace std;
class BinaryTree {

  struct Node {
    char data;
    Node *left = nullptr;
    Node *right = nullptr;
  };

private:
  Node *root;
  void preorder(Node *ptr);
  void inorder(Node *ptr);
  void postorder(Node *ptr);
  int height(Node *ptr);
  void display(Node *ptr, int level);
  Node *construct(char *in, char *pre, int num);
  Node *construct1(char *in, char *post, int num);

public:
  BinaryTree() : root{nullptr} {}
  ~BinaryTree() {};
  bool isEmpty();
  void createTree();
  void preorder();
  void inorder();
  void postorder();
  void levelOrder();
  int height();
  void nrecPreorder();
  void nrecInorder();
  void nrecPostorder();
  void construct(char *in, char *pre);
  void construct1(char *in, char *post);
  void display();
  void nrec_preorder();
  void nrec_inorder();
  // void nrec_postorder();
  void nrec_postorder_two_stack();
  void levelorder();

  void visit(Node *n) { cout << n->data; };
};

void BinaryTree::createTree() {
  // root = new Node('P');
  // root->left = new Node('Q');
  // root->right = new Node('R');
  // root->left->left = new Node('A');
  // root->left->right = new Node('B');
  // root->right->left = new Node('X');
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
  Node *ptr = root;
  stack<Node *> s;
  s.push(ptr);
  while (!s.empty()) {
    ptr = s.top();
    s.pop();
    visit(ptr);

    if (ptr->right)
      s.push(ptr->right);
    if (ptr->left)
      s.push(ptr->left);
  }
  cout << '\n';
}

void BinaryTree::inorder() {
  Node *ptr = root;
  stack<Node *> s;
  while (ptr || !s.empty()) {
    while (ptr) {
      s.push(ptr);
      ptr = ptr->left;
    }
    ptr = s.top();
    s.pop();
    visit(ptr);

    ptr = ptr->right;
  }
  cout << '\n';
}

void BinaryTree::postorder() {
  Node *ptr = root;
  stack<Node *> s;
  stack<Node *> output;
  s.push(ptr);
  while (!s.empty()) {
    ptr = s.top();
    s.pop();
    output.push(ptr);

    if (ptr->left)
      s.push(ptr->left);
    if (ptr->right)
      s.push(ptr->right);
  }
  while (!output.empty()) {

    cout << output.top()->data;
    output.pop();
  }
  cout << '\n';
}

void BinaryTree::levelorder() {
  Node *ptr = root;
  queue<Node *> q;
  q.push(ptr);
  while (!q.empty()) {
    ptr = q.front();
    q.pop();
    visit(ptr);
    if (ptr->left)
      q.push(ptr->left);
    if (ptr->right)
      q.push(ptr->right);
  }
  cout << '\n';
}

int main() {
  BinaryTree tree;
  tree.createTree();
  tree.preorder();   // ABDHECFIGJK
  tree.inorder();    // DHBEAIFCJGK
  tree.postorder();  // HDEBIFJKGCA
  tree.levelorder(); // ABCDEFGHIJK

  string inorder_string = " ABDHECFIGJK"; // sriv p 537
  string preorder_string = "DHBEAIFCJGK";

  string inorder_string2 = "HIDJEBKFGCA";
  string post_order_string2 = "HDIBEJAKFCG";
}
