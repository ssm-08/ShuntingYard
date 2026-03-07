#include <iostream>
#include <cstring>

using namespace std;

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

  void push(Node* node) {
    node->next = top;
    top = node;
  }

  Node* pop() {
    Node* node = top;
    
    if (node != NULL) {
      top = node->next;
      node->next = NULL;
    }

    return node;
    
  }

  Node* peek() {
    return top;
  }
  
};

struct Queue {

  //Head
  Node* front;
  //Last
  Node* rear;

  void enqueue(Node* node) {
    if (rear == NULL) { //First node
      rear = node;
      front = node;
    } else { //Existing nodes
      rear->next = node;
      rear = node;
    }
  }

  Node* dequeue() {
    Node* node = front;
    
    if (node != NULL) { //Existing nodes

      front = node->next;
      node->next = NULL;

      if (front == NULL) { //Last node
	rear = NULL;
      }
    }
    
    return node;
  }
};

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
      run = false;
    } else {
      cout << "Enter expression: ";
      cin.getline(input, 99);
      cout << endl;

      in = createQueue(input);

    }
  }
}

Queue createQueue(char input[99]) {

  Node* front = NULL;
  Node* rear = NULL;
  Queue q = {front, rear};

  for (int i = 0; i < strlen(input); i++) {
    if (input[i] != ' ') {
      char token = input[i];
      Node* node = new Node{token, NULL, NULL, NULL};
      q.enqueue(node);
    }
  }
  
  return q;
}
