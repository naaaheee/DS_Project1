#include "SectionList.h"
#include <iostream>

using namespace std;

SectionList::SectionList() {
    head = nullptr;  // Initialize head to nullptr (empty list)
}

SectionList::~SectionList() {
    clear();  // Clear the list when the SectionList is destroyed
}

void SectionList::clear() {
    SectionListNode* current = head;  // Start with the head node
    while (current != nullptr) {
        SectionListNode* toDelete = current;  // Node to be deleted
        current = current->getNext();  // Move to the next node
        delete toDelete;  // Delete the current node
    }
    head = nullptr;  // Set head to nullptr after clearing the list
}

void SectionList::insertSection(int sectionNumber) {
    // Insert a new section only if it does not already exist
    if (searchSection(sectionNumber) == nullptr) {
        SectionListNode* newSection = new SectionListNode(sectionNumber);  // Create new section node
        if (head == nullptr) {
            head = newSection;  // Set new section as head if list is empty
        }
        else {
            SectionListNode* temp = head;  // Temporary pointer to traverse the list
            while (temp->getNext() != nullptr) {
                temp = temp->getNext();  // Move to the end of the list
            }
            temp->setNext(newSection);  // Append new section to the end of the list
        }
    }
}

SectionListNode* SectionList::searchSection(int sectionNumber) {
    SectionListNode* temp = head;  // Start with the head node
    while (temp != nullptr) {
        if (temp->getSectionNumber() == sectionNumber) {
            return temp;  // Return the section node if found
        }
        temp = temp->getNext();  // Move to the next node
    }
    return nullptr;  // Return nullptr if section is not found
}

void SectionList::addSubtitleToSection(int sectionNumber, SubtitleListNode* subtitle) {
    if (subtitle == nullptr) {
        return; // Do not add if the subtitle node is invalid
    }
    SectionListNode* section = searchSection(sectionNumber);  // Find the section
    if (section != nullptr) {
        section->addContent(subtitle);  // Add subtitle to the found section
    }
}

void SectionList::printSection(int sectionNumber, ofstream& logFile) {
    SectionListNode* section = searchSection(sectionNumber);  // Search for the section
    if (section == nullptr) {
        logFile << "===== ERROR =====\n300\n===============\n";  // Log error if section is not found
        return;
    }
    logFile << "===== PRINT =====\nSection " << sectionNumber << endl;  // Log section header
    SubtitleListNode* content = section->getContentHead();  // Get the head of the subtitle content
    while (content != nullptr) {
        logFile << content->getTime() << " - " << content->getText() << endl;  // Log each subtitle
        content = content->getNext();  // Move to the next subtitle
    }
    logFile << "===============\n" << endl;  // End section log
}
