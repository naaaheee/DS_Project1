#include "SubtitleQueue.h"
#include "SubtitleBST.h"
#include "SectionList.h"
#include <string>
#include <fstream>
using namespace std;

// Class responsible for managing subtitles, their queue, BST, and sections
class Manager {
private:
    ifstream fcmd;          // Input stream for command file
    ofstream flog;          // Output stream for log file
    SubtitleQueue queue;    // Queue for managing subtitles
    SubtitleBST bst;        // Binary search tree for subtitles
    SectionList sectionList; // List of sections for subtitles

public:
    // Constructor to initialize the Manager
    Manager();

    // Destructor to clean up resources
    ~Manager();

    // Method to execute commands from a command file
    void Run(const char* command);

    // Method to print a success message for a given command
    void PrintSuccess(const char* cmd);

    // Method to print an error code
    void PrintErrorCode(int num);

    // Method to add subtitles to a section using in-order traversal
    void inOrderSectionAdd(SubtitleBSTNode* node, int sectionNumber, const string& startTime, const string& endTime);

    // Method to load subtitles from a file
    void load(const char* subtitleFile);

    // Method to pop a subtitle from the queue
    void qpop();

    // Method to print all subtitles
    void print();

    // Method to print subtitles in a specific section
    void printSection(int sectionNumber);

    // Method to specify a range for a section
    void section(int sectionNumber, const string& startTime, const string& endTime);

    // Method to delete a subtitle node based on time and a condition
    void deleteNode(const string& time, const string& condition);
};
