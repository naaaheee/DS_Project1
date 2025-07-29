#include "SubtitleQueueNode.h"
#define MAX_SIZE 100  // Define the maximum size of the queue

using namespace std;

class SubtitleQueue {
private:
    SubtitleQueueNode* queue[MAX_SIZE];  // Array to hold queue nodes
    int front;  // Index of the front of the queue
    int rear;   // Index of the rear of the queue

public:
    SubtitleQueue();  // Constructor to initialize the queue
    ~SubtitleQueue(); // Destructor to clean up resources

    // Check if the queue is empty
    bool isEmpty();

    // Check if the queue is full
    bool isFull();

    // Add a node to the rear of the queue
    void push(SubtitleQueueNode* node);

    // Remove and return the node from the front of the queue
    SubtitleQueueNode* pop();
};
