#include <iostream>
using namespace std;
#define MAX_CHILD_PER_PARENT 10

struct Node {
  int value;
  int child_num;
  Node** children;
  Node* parent;
};

Node* addNode(Node* parent, int value) {
  if (parent->child_num >= MAX_CHILD_PER_PARENT) {
    cout << "the parent node is already full" << endl;
    return NULL;
  }
  Node* node = new Node();

  parent->children[parent->child_num] = node;
  parent->child_num++;
  node->value = value;
  node->parent = parent;
  Node ** child_array = new Node*[MAX_CHILD_PER_PARENT];
  for (int i = 0; i < 10; i++) {
    child_array[i] = NULL;
  }
  node->children = child_array;

  return node;
}

Node* findNode(Node* target_node, int value) {
  Node* node_position = NULL;
  long long node_position_address = 0;
  if (target_node->value != value) {
    int i = 0;
    while (target_node->children[i] != NULL) {
      node_position_address |= (long long)findNode(target_node->children[i], value);
      i++;
    }
    node_position = (Node*)node_position_address;
  } else {
    node_position = target_node;
  }
  return node_position;
}

void showNodeInfo(Node* node, int position) {
  int _position = position;
  while(_position) {
    cout << "   ";
    _position--;
  }
  cout << "+--";
  cout << node->value << endl;
  for (int i = 0; i < node->child_num ; i++) {
    showNodeInfo(node->children[i], position+1);
  }
  return;
}

void deleteNode(Node* node) {
  for (int i = 0; i > node->child_num ; i++) {
    deleteNode(node->children[i]);
  }
  int node_position = 0;
  while(node->parent->children[node_position] != node) {
    node_position++;
  }
  for ( ; node_position < node->parent->child_num-1; node_position++) {
    node->parent->children[node_position] = node->parent->children[node_position+1];
  }
  node->parent->children[node->parent->child_num - 1] = NULL;
  node->parent->child_num--;
  
  delete node;
}

int main() {
  Node* root_node = new Node();
  root_node->value = 0;
  root_node->parent = NULL;
  root_node->children = NULL;
  root_node->child_num = 0;
  Node ** child_array = new Node*[10];
  for (int i = 0; i < 10; i++) {
    child_array[i] = NULL;
  }
  root_node->children = child_array;
  
  addNode(root_node, 3);
  Node *node3 = findNode(root_node, 3);
  Node *node10 = addNode(node3, 10);
  addNode(node10, 30);
  Node *node5 = addNode(root_node, 5);
  Node *node15 = addNode(node3, 15);
  addNode(node15, 34);
  Node *node30 = findNode(root_node, 30);
  showNodeInfo(root_node, 0);
  deleteNode(node10);
  showNodeInfo(root_node, 0);
  addNode(node3, 20);
  addNode(node5, 50);
  showNodeInfo(root_node, 0);

  return 0;
}
  
  
