#include "SubtitleQueue.h"
#include <iostream>

using namespace std;

// Constructor for SubtitleQueue to initialize front and rear indices
SubtitleQueue::SubtitleQueue() {
    front = -1;  // Initialize front index to -1 (indicating an empty queue)
    rear = -1;   // Initialize rear index to -1 (indicating an empty queue)
}

// Destructor for SubtitleQueue to clean up dynamically allocated nodes
SubtitleQueue::~SubtitleQueue() {
    for (int i = front + 1; i <= rear; i++) {
        delete queue[i];  // Delete each node in the queue
    }
}

// Method to check if the queue is empty
bool SubtitleQueue::isEmpty() {
    return front == rear;  // Returns true if front equals rear
}

// Method to check if the queue is full
bool SubtitleQueue::isFull() {
    return rear == MAX_SIZE - 1;  // Returns true if rear has reached maximum size
}

// Method to add a node to the queue
void SubtitleQueue::push(SubtitleQueueNode* node) {
    if (isFull()) {
        cout << "===== ERROR =====\n100\n===============\n";  // Error message if queue is full
        exit(1);  // Exit the program if the queue is full
    }
    queue[++rear] = node;  // Increment rear and add the new node to the queue
}

// Method to remove and return a node from the queue
SubtitleQueueNode* SubtitleQueue::pop() {
    if (isEmpty()) {
        cout << "===== ERROR =====\n200\n===============\n";  // Error message if queue is empty
        exit(1);  // Exit the program if the queue is empty
    }
    return queue[++front];  // Increment front and return the node at the front of the queue
}
