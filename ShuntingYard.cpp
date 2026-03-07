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

  bool isNum() {
    return isdigit(token);
  }
  
  bool isOperator() {
    if (token == '^') {
      return true;
    } else if (token == '*' || token == '/') {
      return true;
    } else if (token == '+' || token == '-') {
      return true;
    } else {
      return false;
    }
  }

  int getOrder() {
    if (token == '^') {
      return 3;
    } else if (token == '*' || token == '/') {
      return 2;
    } else if (token == '+' || token == '-') {
      return 1;
    } else {
      return -1;
    }    
  }

  bool isRight() {
    if (token == '^') {
      return true;
    } else {
      return false;
    }
  }
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
Queue ShuntYard(Queue q);
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

Queue ShuntYard(Queue in) {
  Stack s = {NULL};
  Queue out = {NULL, NULL};

  while (in.front != NULL) {

    Node* node = in.front;
    
    //Remove node from input
    in.dequeue();
    
    if (node->isNum()) { // Add number to out queue
      out.enqueue(node);
    } else if (node->token == '(') { // Add left par to stack
      s.push(node);
    } else if (node->token == ')') { // Remove operators for right par

      // Pop operators until left par is reached
      while (s.peek() != NULL &&
	     s.peek()->token != '(') {
	out.enqueue(s.pop());
      }

      //Remove left par
      s.pop();
      
    } else if (node->isOperator()) { // Add operators to stack

      // Pop left associative operators to queue if order is higher
      while (s.peek() != NULL &&
	     node->getOrder() <= s.peek()->getOrder() && !s.peek()->isRight()) {

	out.enqueue(s.pop());
      }
      
      s.push(node);
    }
  }

  //Add remaining operators to queue
  while (s.peek() != NULL) {
    out.enqueue(s.pop());
  }

  return out;
}
