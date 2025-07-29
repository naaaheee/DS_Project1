#include <string>
using namespace std;

// Class representing a node in a binary search tree for subtitles
class SubtitleBSTNode {
private:
    string time;  // Time of the subtitle
    string text;  // Content of the subtitle
    SubtitleBSTNode* left;   // Pointer to the left child node
    SubtitleBSTNode* right;  // Pointer to the right child node

public:
    // Constructor to initialize the subtitle node with time and text
    SubtitleBSTNode(string t, string tx)
        : time(t), text(tx), left(nullptr), right(nullptr) {}

    // Getter for subtitle time
    string getTime() { return time; }

    // Getter for subtitle text
    string getText() { return text; }

    // Getter for the left child node
    SubtitleBSTNode* getLeft() { return left; }

    // Getter for the right child node
    SubtitleBSTNode* getRight() { return right; }

    // Setter for the left child node
    void setLeft(SubtitleBSTNode* node) { left = node; }

    // Setter for the right child node
    void setRight(SubtitleBSTNode* node) { right = node; }

    // Setter for the subtitle time
    void setTime(const string& newTime) { time = newTime; }

    // Setter for the subtitle text
    void setText(const string& newText) { text = newText; }
};
