#include <iostream>
#include <vector>
using namespace std;

enum NodeType { LeafNode, InternalNode };

template <typename T> struct BTreeNode {
  NodeType type;
  vector<T> keys;
  vector<BTreeNode<T> *> children;

public:
  BTreeNode(NodeType type) : type(type) {}
  BTreeNode(T val, NodeType type) : type(type) { this->keys.push_back(val); }
};

template <typename T> class BTree {
  size_t max_degree;
  BTreeNode<T> *root;

public:
  BTree(int max_degree) : max_degree(max_degree), root(nullptr) {}

  void insert(T val) {
    if (root == nullptr) {
      BTreeNode<T> *new_root = new BTreeNode<T>(val, NodeType::LeafNode);
      this->root = new_root;
      return;
    }

    if (root->keys.size() == max_degree - 1) {
      /*the root is full*/
      BTreeNode<T> *new_root = new BTreeNode<T>(NodeType::InternalNode);
      new_root->children.push_back(root);
      split_node(new_root, 0);
      root = new_root;
    }
    insert_not_full(root, val);
  }

  void display() { traverse(root); }

private:
  void split_node(BTreeNode<T> *parent, int index) {
    BTreeNode<T> *child = parent->children[index];
    BTreeNode<T> *new_node = new BTreeNode<T>(child->type);

    // move child keys to new node
    for (size_t i = max_degree / 2 + 1; i < child->keys.size(); i++) {
      new_node->keys.push_back(child->keys[i]);
    }

    if (child->type != NodeType::LeafNode) {
      // move the children pointers
      for (size_t i = max_degree / 2 + 1; i < child->children.size(); i++) {
        new_node->children.push_back(child->children[i]);
      }
    }

    // link the new node to the parent node
    parent->children.insert(parent->children.begin() + index + 1, new_node);

    // add the middle elm of child to parent
    parent->keys.insert(parent->keys.begin() + index,
                        child->keys[max_degree / 2 - 1]);

    // clean up the child
    child->keys.erase(child->keys.begin() + max_degree / 2 - 1,
                      child->keys.end());
    if (child->type != NodeType::LeafNode) {
      child->children.erase(child->children.begin() + max_degree / 2 - 1,
                            child->children.end());
    }
  }

  void insert_not_full(BTreeNode<T> *node, T val) {
    int i = node->keys.size() - 1;
    if (node->type == NodeType::LeafNode) {
      while (i >= 0 && node->keys[i] > val) {
        i--;
      }
      node->keys.insert(node->keys.begin() + i + 1, val);
      return;
    }
    // find the child
    while (i >= 0 && node->keys[i] > val) {
      i--;
    }
    // adjust for index of child
    i++;

    if (node->children[i]->keys.size() == max_degree - 1) {
      // split the child
      split_node(node, i);

      if (node->keys[i] < val) {
        i++;
      }
    }
    insert_not_full(node->children[i], val);
  }

  void traverse(BTreeNode<T> *root) {
    if (root == nullptr)
      return;

    for (const auto &i : root->keys) {
      cout << i << " ";
    }
    cout << endl;
    for (size_t i = 0; i < root->children.size(); i++) {
      traverse(root->children[i]);
    }
  }
};

int main() {
  BTree<int> btree(5);
  btree.insert(10);
  btree.insert(20);
  btree.insert(5);
  btree.insert(6);
  btree.insert(110);
  btree.insert(12);
  btree.insert(30);
  btree.insert(60);
  btree.insert(80);
  btree.insert(90);
  btree.insert(100);

  btree.display();
  return 0;
}
