#include "SubtitleBST.h"
#include <iostream>

using namespace std;

// Constructor: Initializes the root of the binary search tree to nullptr
SubtitleBST::SubtitleBST() {
    root = nullptr;  // Set the root to null
}

// Destructor: Calls the clear function to free memory
SubtitleBST::~SubtitleBST() {
    clear(root);  // Clear the tree when the object is destroyed
}

// Recursively deletes nodes in the tree
void SubtitleBST::clear(SubtitleBSTNode* node) {
    if (node == nullptr) return;  // Base case: if the node is null, return
    clear(node->getLeft());       // Clear the left subtree
    clear(node->getRight());      // Clear the right subtree
    delete node;                  // Delete the current node
}

// Function to insert a subtitle
void SubtitleBST::insert(string time, string text) {
    insertHelper(root, time, text);  // Call helper function to insert
}

// Recursive helper function to insert a node
void SubtitleBST::insertHelper(SubtitleBSTNode*& node, string time, string text) {
    if (node == nullptr) {
        node = new SubtitleBSTNode(time, text);  // Create a new node if it's null
    }
    else if (time < node->getTime()) {
        SubtitleBSTNode* leftChild = node->getLeft(); // Store left child as lvalue
        insertHelper(leftChild, time, text);  // Insert into the left subtree
        node->setLeft(leftChild);               // Update the left child
    }
    else {
        SubtitleBSTNode* rightChild = node->getRight(); // Store right child as lvalue
        insertHelper(rightChild, time, text);  // Insert into the right subtree
        node->setRight(rightChild);             // Update the right child
    }
}

// Function to search for a subtitle by time
SubtitleBSTNode* SubtitleBST::search(string time) {
    return searchHelper(root, time);  // Call helper function to search
}

// Recursive helper function to search for a subtitle
SubtitleBSTNode* SubtitleBST::searchHelper(SubtitleBSTNode* node, string time) {
    if (node == nullptr || node->getTime() == time) {
        return node;  // Return if node is null or time matches
    }
    else if (time < node->getTime()) {
        return searchHelper(node->getLeft(), time);  // Search in the left subtree
    }
    else {
        return searchHelper(node->getRight(), time); // Search in the right subtree
    }
}

// Function to print subtitles in in-order traversal
void SubtitleBST::printInOrder(ofstream& logFile) {
    if (root != nullptr) {
        printInOrderHelper(root, logFile);  // Call helper function to print
    }
}

// Recursive helper function to print subtitle nodes in in-order
void SubtitleBST::printInOrderHelper(SubtitleBSTNode* node, ofstream& logFile) {
    if (node->getLeft() != nullptr) {
        printInOrderHelper(node->getLeft(), logFile);  // Print left subtree
    }
    logFile << node->getTime() << " - " << node->getText() << endl; // Print subtitle
    if (node->getRight() != nullptr) {
        printInOrderHelper(node->getRight(), logFile); // Print right subtree
    }
}

// Function to delete a subtitle node by time
void SubtitleBST::deleteNode(string time) {
    root = deleteHelper(root, time);  // Call helper function to delete
}

// Recursive helper function to delete a subtitle node
SubtitleBSTNode* SubtitleBST::deleteHelper(SubtitleBSTNode* node, string time) {
    if (node == nullptr) return nullptr;  // Return if node is null

    // Conditions for finding the node to delete
    if (time < node->getTime()) {
        node->setLeft(deleteHelper(node->getLeft(), time));  // Delete from left subtree
    }
    else if (time > node->getTime()) {
        node->setRight(deleteHelper(node->getRight(), time)); // Delete from right subtree
    }
    else {
        // Node to delete is found
        if (node->getLeft() == nullptr) {
            SubtitleBSTNode* temp = node->getRight();  // Store right child
            delete node;  // Delete current node
            return temp;  // Return right child to connect to parent
        }
        else if (node->getRight() == nullptr) {
            SubtitleBSTNode* temp = node->getLeft();   // Store left child
            delete node;  // Delete current node
            return temp;  // Return left child to connect to parent
        }
        else {
            // If the node has two children, find the minimum node in the right subtree
            SubtitleBSTNode* minNode = findMin(node->getRight());  // Find minimum node

            // Swap data with the minimum node
            node->setTime(minNode->getTime());
            node->setText(minNode->getText());

            // Delete the minimum node from the right subtree
            node->setRight(deleteHelper(node->getRight(), minNode->getTime()));
        }
    }
    return node;  // Return the modified current node
}

// Function to delete nodes with timestamps less than the given time
void SubtitleBST::deleteUnder(string time) {
    root = deleteUnderHelper(root, time);  // Call helper function to delete
}

// Recursive helper function to delete nodes with timestamps less than the given time
SubtitleBSTNode* SubtitleBST::deleteUnderHelper(SubtitleBSTNode* node, const string& time) {
    if (node == nullptr) {
        return nullptr;  // Base case: return nullptr if the node is null
    }

    // Perform delete operation on the left subtree
    node->setLeft(deleteUnderHelper(node->getLeft(), time));

    // Delete the current node if its time is less than the given time
    if (node->getTime() < time) {
        SubtitleBSTNode* rightChild = node->getRight();  // Store the right child
        delete node;  // Delete the current node
        return rightChild;  // Return right child to connect to parent
    }

    // Perform delete operation on the right subtree
    node->setRight(deleteUnderHelper(node->getRight(), time));

    return node;  // Return the modified current node
}

// Function to find the minimum node in a subtree
SubtitleBSTNode* SubtitleBST::findMin(SubtitleBSTNode* node) {
    while (node->getLeft() != nullptr) {
        node = node->getLeft();  // Move to the left child
    }
    return node;  // Return minimum node
}

// Function to search for the next subtitle after a given time
SubtitleBSTNode* SubtitleBST::searchNext(const string& currentTime) {
    SubtitleBSTNode* currentNode = search(currentTime);  // Search for the current time subtitle
    if (currentNode == nullptr) return nullptr;  // Return if not found

    // If there is a right subtree, find the minimum node in it
    if (currentNode->getRight() != nullptr) {
        return findMin(currentNode->getRight());
    }

    // Traverse up the tree to find the first ancestor for which the current node is in the left subtree
    SubtitleBSTNode* successor = nullptr;
    SubtitleBSTNode* ancestor = root;  // Start from the root of the BST
    while (ancestor != currentNode) {
        if (currentNode->getTime() < ancestor->getTime()) {
            successor = ancestor;  // Potential successor
            ancestor = ancestor->getLeft();  // Move to left child
        }
        else {
            ancestor = ancestor->getRight(); // Move to right child
        }
    }
    return successor;  // Return successor
}

// Function to return the root of the tree
SubtitleBSTNode* SubtitleBST::getRoot() const {
    return root;  // Return the root node
}
