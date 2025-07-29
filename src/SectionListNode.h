#ifndef SECTIONLISTNODE_H
#define SECTIONLISTNODE_H

#include "SubtitleListNode.h"
using namespace std;

// Class representing a node for a section containing subtitles
class SectionListNode {
private:
    int sectionNumber;               // Section number
    SubtitleListNode* contentHead;   // Pointer to the first subtitle node in the section
    SectionListNode* next;           // Pointer to the next section node

public:
    // Constructor to initialize the section node with a section number
    SectionListNode(int num) : sectionNumber(num), contentHead(nullptr), next(nullptr) {}

    // Getter for the section number
    int getSectionNumber() { return sectionNumber; }

    // Getter for the head of the content nodes (subtitles)
    SubtitleListNode* getContentHead() { return contentHead; }

    // Getter for the next section node
    SectionListNode* getNext() { return next; }

    // Setter for the next section node
    void setNext(SectionListNode* node) { next = node; }

    // Method to add a subtitle content node to the section
    void addContent(SubtitleListNode* content) {
        if (contentHead == nullptr) {
            contentHead = content; // Set as the first subtitle node
        }
        else {
            SubtitleListNode* temp = contentHead;
            while (temp->getNext() != nullptr) {
                temp = temp->getNext(); // Move to the last subtitle node
            }
            temp->setNext(content); // Add the new subtitle node
        }
    }
};

#endif
