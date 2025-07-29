#include "SectionListNode.h"
#include <fstream>

using namespace std;

// Class representing a list of sections, each containing subtitles
class SectionList {
private:
    SectionListNode* head;  // Pointer to the head of the section list

public:
    // Constructor to initialize the section list
    SectionList();

    // Destructor to clean up resources
    ~SectionList();

    // Method to insert a new section with a given section number
    void insertSection(int sectionNumber);

    // Method to search for a section by its section number
    SectionListNode* searchSection(int sectionNumber);

    // Method to add a subtitle to a specific section
    void addSubtitleToSection(int sectionNumber, SubtitleListNode* subtitle);

    // Method to print the contents of a specific section to a log file
    void printSection(int sectionNumber, ofstream& logFile);

private:
    // Method to clear the section list and free resources
    void clear();
};
