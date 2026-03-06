#include <iostream>
#include <cstring>

//Data structures
struct Node {

  char token;

  //Linked list
  Node* next;

  //Binary tree
  Node* left;
  Node* right;

};

struct Stack {
  //Head
  Node* top;
};

struct Queue {

  //Head
  Node* front;

  Node* rear;
};


//Stack functions
void push();
Node* pop();
Node* peek();

//Queue functions
void enqueue(Queue& queue, Node* node);
Node* dequeue();

//Program functions
Queue createQueue(char input[99]);
void ShuntYard();
void createTree();


int main() {

  Queue in = {NULL, NULL};
  Queue out {NULL, NULL};

  bool run = true;
  
  char input[99] = "";

  while (run == true) {

    if (strcmp(input, "QUIT") == 0) {
      run == false;
    } else {

   
      
    }
  }
}

Queue createQueue(char input[99]) {

  Node* front = NULL;
  Node* rear = NULL;
  Queue queue = {front, rear};

  for (int i = 0; i < strlen(input); i++) {
    if (input[i] != ' ') {
      char token = input[i];
      Node* node = new Node{token, NULL, NULL, NULL};
      enqueue(queue, node);
    }
  }
  
  return queue;
}

void enqueue(Queue& queue, Node* node) {
  if (queue.rear == NULL) {
    queue.rear = node;
    queue.front = node;
  } else {
    queue.rear->next = node;
    queue.rear = node;
  }
}
