#include <string>
using namespace std;

class SubtitleQueueNode {
private:
    string time;  // Time of the subtitle
    string text;  // Text of the subtitle

public:
    // Constructor to initialize the subtitle node with time and text
    SubtitleQueueNode(string t, string tx) : time(t), text(tx) {}

    // Getter for the subtitle time
    string getTime() { return time; }

    // Getter for the subtitle text
    string getText() { return text; }
};
