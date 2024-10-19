#include <iostream>

using namespace std;

class Node
{
    public:
        int value;
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
        int get_balance_factor(Node* node);
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
        Node* insert(Node* node, int value);
        Node* delete_node(Node* node, int value);

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
    return node ? node -> height : 0;
}






/* Helper methods
 * Returns the balance factor of the node
 * The balance factor of a node is the height of the left child - the height
 * of the right child
*/
int AVL::get_balance_factor(Node* node)
{
    int Rh = (node && node -> right_child) ? node -> right_child -> height : 0;
    int Lh = (node && node -> left_child) ? node -> left_child -> height : 0;
    // Return the balance factor of the node
    return  Lh - Rh;
}






/*
 * Helper method
 * Performs a left rotation on the node
 * Returns the new node
*/
Node* AVL::left_rotate(Node* node)
{
    // Create a new node to store the left child of the node
    Node* right_node = node -> right_child;
    // Create a new node to stor the left child of the left child of the node
    Node* right_node_left_child = right_node -> left_child;

    // Set the left child of the new node to be the node
    right_node -> left_child = node;
    // Set the right child of the node to be the left child of the left child of the node
    node -> right_child = right_node_left_child;

    // Update the height of the node
    node -> height = max(height(node -> left_child), height(node -> right_child)) + 1;
    // Update the height of the new node
    right_node -> height = max(height(right_node -> left_child), height(right_node -> right_child)) + 1;

    // Update the root of the tree
    if (node == root) root = right_node;

    // Return the new node
    return right_node;
}





/*
 * Helper method
 * Performs a right rotation on the node
 * Returns the new node
*/
Node* AVL::right_rotate(Node* node)
{
    // Create a new pointer to point to the left child of the node
    Node* left_node = node -> left_child;
    // Create a new pointer to point to the right child of the left child of the node
    Node* left_node_right_child = left_node -> right_child;
    // Set the right child of the left_node to be the node
    left_node -> right_child = node;
    // Set the left child of the node to be the right child of the left child of the node
    node -> left_child = left_node_right_child;

    // Update the height of the node
    node -> height = max(height(node -> left_child), height(node -> right_child)) + 1;
    // Update the height of the new root
    left_node -> height = max(height(left_node -> left_child), height(left_node -> right_child)) + 1;

    // Update the root of the tree
    if (node == root) root = left_node;

    // Return the new root
    return left_node;
}







/*
 * Helper method
 * Inserts a new node into the tree
 * Returns the new node
*/

Node* AVL::insert(Node* node, int value)
{
    // If the root is NULL, create a new node and set its key to the value
    if (!node)
    {
        Node* new_node = new Node();
        new_node -> value = value;
        new_node -> height = 1;
        return new_node;
    }

    // If the value is less than the key of the root, insert the value into the
    // left child of the root and update the height of the root
    if (value < node -> value)
    {
        node -> left_child = insert(node -> left_child, value);
    }
    else if (value > node -> value)
    {
        // If the value is greater than the value of the root, insert the value into the
        // right child of the node
        node -> right_child = insert(node -> right_child, value);
    }
    else
    {
        // If the value is equal to the value of the root, return the root
        // Equal values are not allowed in BST
        return node;
    }


    // Update the height of the root
    node -> height = max(height(node -> left_child), height(node -> right_child)) + 1;


    // Get the balance factor
    int balance_factor = get_balance_factor(node);

    // Balancing the tree
    // Left Left Case
    if (balance_factor > 1 && value < node -> left_child -> value) return right_rotate(node);

    // Right Right Case
    if (balance_factor < -1 && value > node -> right_child -> value) return left_rotate(node);

    // Left Right Case
    if (balance_factor > 1 && value > node -> left_child -> value)
    {
        node -> left_child = left_rotate(node -> left_child);
        return right_rotate(node);
    }

    // Right Left Case
    if (balance_factor < -1 && value < node -> right_child -> value)
    {
        node -> right_child = right_rotate(node -> right_child);
        return left_rotate(node);
    }

    // Return the root
    return node;
}




/*
 * Helper method
 * Traverses the tree in inorder fashion and prints the values of the nodes
 * Returns the node with the minimum value
*/
void AVL::inorder(Node* root)
{
    if (root)
    {
        inorder(root -> left_child);
        cout << root -> value << " ";
        inorder(root -> right_child);
    }

}




int main()
{
    AVL avl;
    avl.root = avl.insert(avl.root, 10);
    avl.root = avl.insert(avl.root, 20);
    avl.root = avl.insert(avl.root, 30);
    avl.root = avl.insert(avl.root, 40);
    avl.root = avl.insert(avl.root, 50);
    avl.root = avl.insert(avl.root, 25);

    avl.inorder();
    return 0;
}