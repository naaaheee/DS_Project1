#include "SubtitleBSTNode.h"
#include <fstream>  // Include for file output
using namespace std;

// Binary Search Tree class for subtitles
class SubtitleBST {
private:
    SubtitleBSTNode* root;  // Root node of the tree
    SubtitleBSTNode* deleteUnderHelper(SubtitleBSTNode* node, const string& time);  // Helper function for deleting nodes under a specific time

public:
    SubtitleBST();  // Constructor to initialize the BST
    ~SubtitleBST(); // Destructor to clean up the tree

    // Method to insert a new subtitle into the BST
    void insert(string time, string text);

    // Method to print subtitles in order to a log file
    void printInOrder(ofstream& logFile);

    // Method to search for a subtitle by time
    SubtitleBSTNode* search(string time);

    // Method to delete a specific subtitle node
    void deleteNode(string time);

    // Method to delete all nodes under a specific time
    void deleteUnder(string time);

    // Method to search for the next subtitle node after a given time
    SubtitleBSTNode* searchNext(const string& currentTime);

    // Method to find the minimum node in a subtree
    SubtitleBSTNode* findMin(SubtitleBSTNode* node);

    // Method to get the root node of the BST
    SubtitleBSTNode* getRoot() const;

private:
    // Helper method to insert a new subtitle into the tree
    void insertHelper(SubtitleBSTNode*& node, string time, string text);

    // Helper method to print subtitles in order
    void printInOrderHelper(SubtitleBSTNode* node, ofstream& logFile);

    // Helper method to search for a subtitle node
    SubtitleBSTNode* searchHelper(SubtitleBSTNode* node, string time);

    // Helper method to delete a subtitle node
    SubtitleBSTNode* deleteHelper(SubtitleBSTNode* node, string time);

    // Helper method to clear the tree
    void clear(SubtitleBSTNode* node);
};
