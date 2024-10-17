#include <iostream>

using namespace std;

class Node
{
    public:
        int key;
        Node* parent;
        Node* left_child;
        Node* right_child;
        int height;
};

class AVL
{
    public:
        Node* root;

        AVL(){root = NULL;}

        // Helper methods
        int height(Node* node);
        int balance_factor(Node* node);
        Node* left_rotate(Node* node);
        Node* right_rotate(Node* node);
        Node* left_right_rotate(Node* node);
        Node* right_left_rotate(Node* node);
        Node* find_min(Node* root);
        Node* find_max(Node* root);
        Node* find_successor(Node* root);
        Node* find_predecessor(Node* root);
        void preorder(Node* root);
        void postorder(Node* root);

        // Insertion and Deletion
        Node* insert(Node* root, int value);
        Node* delete_node(Node* root, int value);

        // Traversal
        void inorder(Node* root);
        void inorder(){ inorder(root);}
        Node* get_root() { return root;}

        // Search
        Node* search(Node* root, int value);
        int NodeHeight (Node* node);
};



/* Helper methods
 * Returns the height of the node
 * If the node is NULL, returns 0
 * Otherwise, returns the height of the node
 * The height of a node is the maximum height of its children + 1
*/
int AVL::height(Node* node)
{
    // If the node exist and the left child exist, return the height of the left child
    int h_left = (node && node -> left_child) ? node -> left_child -> height : 0;
    // If the node exist and the right child exist, return the height of the right child
    int h_right = (node && node -> right_child) ? node -> right_child -> height : 0;

    // Return the maximum height of the children + 1
    return (h_left > h_right) ? h_left + 1 : h_right + 1;
}






/* Helper methods
 * Returns the balance factor of the node
 * The balance factor of a node is the height of the left child - the height of the right child
*/
int AVL::balance_factor(Node* node)
{
    // If the node exist and the left child exist, return the height of the left child
    int h_left = (node && node -> left_child) ? node -> left_child -> height : 0;
    // If the node exist and the right child exist, return the height of the right child
    int h_right = (node && node -> right_child) ? node -> right_child -> height : 0;

    // Return the balance factor of the node
    return h_left - h_right;
}






/*
 * Helper method
 * Performs a left rotation on the node
 * Returns the new node
*/
Node* AVL::left_rotate(Node* node)
{
    // Create a new node to store the left child of the node
    Node* node_left = node -> left_child;
    // Create a new node to stor the left child of the left child of the node
    Node* node_left_child_right_child = node_left -> right_child;

    // Set the left child of the new node to be the node
    node_left -> right_child = node;
    // Set the right child of the node to be the left child of the left child of the node
    node -> left_child = node_left_child_right_child;

    // Update the height of the node
    node -> height = height(node);
    // Update the height of the new node
    node_left -> height = height(node_left);

    // Update the root of the tree
    if (node == root) root = node_left;

    // Return the new node
    return node_left;
}