# B-Tree Implementation in C++

This repository contains a simple implementation of the **B-Tree** data structure in C++. A B-Tree is a self-balancing search tree that maintains sorted data, providing efficient **insertion**, **deletion**, and **searching** operations.

This implementation supports the following operations:

- **Insertion**
- **Searching**
- **Display (Traverse and display the tree)**
  
## Code Overview

### BTreeNode Struct
The `BTreeNode` struct represents a node in the B-Tree, containing:
- `type`: The type of the node (`LeafNode` or `InternalNode`).
- `keys`: A vector of keys stored in the node.
- `children`: A vector of pointers to child nodes.

### BTree Class
The `BTree` class manages the overall tree structure and supports the following methods:
- `insert`: Inserts a value into the tree, creating new nodes as necessary and splitting full nodes.
- `search`: Searches for a value in the tree, returning `true` if found and `false` otherwise.
- `display`: Prints the keys in the tree using a pre-order traversal.

### Helper Functions
- `split_node`: Handles splitting a full node during insertion.
- `insert_not_full`: Inserts a value into a node that is not full.
- `traverse`: A pre-order traversal to display the tree structure.
- `search_helper`: Recursively searches for a value in the tree.
- `delete_helper`: Recursively deletes nodes and frees memory.
