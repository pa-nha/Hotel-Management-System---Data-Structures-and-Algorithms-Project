#include "../include/Tree.h"
#include <iostream>
#include <cstring>
using namespace std;

void initHotelTree(HotelTree &tree) {
    tree.root = nullptr;
}

Node* insert(Node* root, int data, const char* desc) {
    if (root == nullptr) {
        root = new Node;
        root->data = data;
        strcpy(root->description, desc);
        root->left = nullptr;
        root->right = nullptr;
    } else if (data < root->data) {
        root->left = insert(root->left, data, desc);
    } else if (data > root->data) {
        root->right = insert(root->right, data, desc);
    }
    return root;
}

Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

bool search(Node* root, int data) {
    if (root == nullptr) {
        return false;
    } else if (data == root->data) {
        cout << "Floor " << data << ": " << root->description << "\n";
        return true;
    } else if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

int getSize(Node* root) {
    if (root == nullptr) {
        return 0;
    } else {
        return (1 + getSize(root->left) + getSize(root->right));
    }
}

void preorder(Node* root) {
    if (root != nullptr) {
        cout << "Floor " << root->data << " (" << root->description << ")\n";
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << "Floor " << root->data << " (" << root->description << ")\n";
        inorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << "Floor " << root->data << " (" << root->description << ")\n";
    }
}

void deleteNode(Node*& root, int data) {
    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr && current->data != data) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) {
        cout << "Floor " << data << " not found in the tree.\n";
        return;
    }

    if (current->left == nullptr && current->right == nullptr) {
        if (current != root) {
            if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }
        delete current;
    } else if (current->left != nullptr && current->right != nullptr) {
        Node* rightMin = findMin(current->right);
        int val = rightMin->data;
        char desc[50];
        strcpy(desc, rightMin->description);
        deleteNode(root, rightMin->data);
        current->data = val;
        strcpy(current->description, desc);
    } else {
        Node* child = (current->left) ? current->left : current->right;
        if (current != root) {
            if (current == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else {
            root = child;
        }
        delete current;
    }
}
