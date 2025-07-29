#include "Manager.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Manager::Manager() {
    // Constructor initialization
}

Manager::~Manager() {
    // Destructor to release any resources if needed
}

void Manager::Run(const char* command) {
    // Open the command file and log file
    fcmd.open(command);
    flog.open("log.txt");

    if (!fcmd.is_open()) {
        flog << "Fail to open command file" << endl;
        exit(-1);  // Exit the program if the command file cannot be opened
    }

    string line;
    while (getline(fcmd, line)) {
        istringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "LOAD") {
            string extra;
            if (ss >> extra) {  // If there's an extra argument, print error
                PrintErrorCode(100);
            }
            else {
                load("subtitle.txt");  // Load the subtitle file
            }
        }
        else if (cmd == "QPOP") {
            string extra;
            if (ss >> extra) {  // If there's an extra argument, print error
                PrintErrorCode(200);
            }
            else {
                qpop();  // Pop subtitles from the queue
            }
        }
        else if (cmd == "PRINT") {
            string sectionNumberStr, extra;
            if (ss >> sectionNumberStr) {
                if (ss >> extra) {  // If there are too many arguments, print error
                    PrintErrorCode(300);
                }
                else {
                    printSection(stoi(sectionNumberStr));  // Print a specific section
                }
            }
            else {
                print();  // Print all subtitles
            }
        }
        else if (cmd == "SECTION") {
            int sectionNumber;
            string startTime, endTime, extra;
            if (!(ss >> sectionNumber >> startTime >> endTime)) {  // If there are not enough arguments, print error
                PrintErrorCode(400);
            }
            else if (ss >> extra) {  // If there are too many arguments, print error
                PrintErrorCode(400);
            }
            else {
                section(sectionNumber, startTime, endTime);  // Define the section range
            }
        }
        else if (cmd == "DELETE") {
            string condition, time, extra;
            if (!(ss >> condition >> time)) {  // If there are not enough arguments, print error
                PrintErrorCode(500);
            }
            else if (ss >> extra) {  // If there are too many arguments, print error
                PrintErrorCode(500);
            }
            else {
                deleteNode(time, condition);  // Delete a node
            }
        }
        else if (cmd == "EXIT") {
            PrintSuccess("EXIT");
            break;  // Exit the loop
        }
        else {
            PrintErrorCode(1000);  // Invalid command
        }
    }

    // Close the command file and log file
    fcmd.close();
    flog.close();
}

void Manager::PrintSuccess(const char* cmd) {
    // Print a success message to the log
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============\n" << endl;
}

void Manager::PrintErrorCode(int num) {
    // Print an error message to the log
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============\n" << endl;
}

void Manager::load(const char* subtitleFile) {
    // Load the subtitles from the file
    ifstream file(subtitleFile);
    if (!file.is_open()) {
        PrintErrorCode(100); // File opening failed
        return;
    }

    string line;
    flog << "==== LOAD ==== " << endl;
    while (getline(file, line)) {
        istringstream ss(line);
        string time, text;
        ss >> time;
        getline(ss, text);

        // Add subtitle information to the queue
        if (!queue.isFull()) {
            queue.push(new SubtitleQueueNode(time, text));
            flog << time << " - " << text << endl; // Log the added subtitle
        }
    }
    flog << "===============\n" << endl;

    file.close();
}

void Manager::qpop() {
    try {
        if (queue.isEmpty()) {
            PrintErrorCode(200);  // Print error if the queue is empty
            return;
        }

        while (!queue.isEmpty()) {
            SubtitleQueueNode* node = queue.pop();
            if (node) {
                bst.insert(node->getTime(), node->getText());
                delete node;  // Free memory
            }
            else {
                throw std::runtime_error("Attempted to pop a null node from queue.");
            }
        }

        PrintSuccess("QPOP");
    }
    catch (const std::exception& e) {
        flog << "Exception: " << e.what() << endl;
        abort(); // Call abort on exception
    }
}

void Manager::print() {
    // Print all subtitles to the log
    flog << "===== PRINT =====" << endl; // Start message for printing
    flog << "Subtitle_BST" << endl; // Print the name of the BST
    bst.printInOrder(flog); // Output the BST in-order
    flog << "===============\n" << endl; // Separator
}

void Manager::printSection(int sectionNumber) {
    // Print the subtitles of a specific section to the log
    sectionList.printSection(sectionNumber, flog);
}

void Manager::section(int sectionNumber, const string& startTime, const string& endTime) {
    // Add a header node to the section list by section number
    sectionList.insertSection(sectionNumber);

    // Check for nodes in the BST by performing in-order traversal
    SubtitleBSTNode* node = bst.getRoot();
    if (node == nullptr) {
        PrintErrorCode(400);  // Print error if the BST is empty
        return;
    }

    // Perform in-order traversal and add nodes within the time range to the section list
    inOrderSectionAdd(node, sectionNumber, startTime, endTime);
    PrintSuccess("SECTION");
}

void Manager::inOrderSectionAdd(SubtitleBSTNode* node, int sectionNumber, const string& startTime, const string& endTime) {
    if (node == nullptr) return;

    // Visit the left subtree
    inOrderSectionAdd(node->getLeft(), sectionNumber, startTime, endTime);

    // Check if the current node's time is within the range
    if (node->getTime() >= startTime && node->getTime() <= endTime) {
        sectionList.addSubtitleToSection(sectionNumber, new SubtitleListNode(node->getTime(), node->getText()));
    }

    // Visit the right subtree
    inOrderSectionAdd(node->getRight(), sectionNumber, startTime, endTime);
}

void Manager::deleteNode(const string& time, const string& condition) {
    // Check if the root of the Subtitle_BST is null
    if (bst.getRoot() == nullptr) { // If root is null, the BST is empty
        PrintErrorCode(500);  // Print error if the BST is empty
        return;
    }

    if (condition == "EQUAL") {
        SubtitleBSTNode* nodeToDelete = bst.search(time);  // Find the node matching the specific time
        if (nodeToDelete != nullptr) { // If the node exists
            bst.deleteNode(time);  // Delete the node
            PrintSuccess("DELETE");
        }
        else {
            PrintErrorCode(500);  // Print error if the node to delete does not exist
        }
    }
    else if (condition == "UNDER") {
        // Delete all nodes before the specified time
        bst.deleteUnder(time);  // Delete nodes older than the specified time
        PrintSuccess("DELETE");
    }
    else {
        PrintErrorCode(500);  // Print error for invalid condition
    }
}
