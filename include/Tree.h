#ifndef TREE_H
#define TREE_H

struct Node {
    int data;
    char description[50];
    Node* left;
    Node* right;
};

struct HotelTree {
    Node* root;
};

void initHotelTree(HotelTree &tree);
Node* insert(Node* root, int data, const char* desc);
Node* findMin(Node* root);
bool search(Node* root, int data);
int getSize(Node* root);
void preorder(Node* root);
void inorder(Node* root);
void postorder(Node* root);
void deleteNode(Node*& root, int data);

#endif
