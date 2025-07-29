#include <string>
using namespace std;

// Class representing a node for subtitle content
class SubtitleListNode {
private:
    string time;  // Time of the subtitle
    string text;  // Content of the subtitle
    SubtitleListNode* next; // Pointer to the next subtitle node

public:
    // Constructor to initialize the subtitle node with time and text
    SubtitleListNode(string t, string tx) : time(t), text(tx), next(nullptr) {}

    // Getter for subtitle time
    string getTime() { return time; }

    // Getter for subtitle text
    string getText() { return text; }

    // Getter for the next subtitle node
    SubtitleListNode* getNext() { return next; }

    // Setter for the next subtitle node
    void setNext(SubtitleListNode* node) { next = node; }
};
