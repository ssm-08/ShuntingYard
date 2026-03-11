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

  bool isLeft() {
    if (token == '^') {
      return false;
    } else {
      return true;
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
Queue ShuntYard(Queue in);
Stack createTree(Queue in);

void print(Node* node, int n);

int main() {

  //Set up program variables and input
  
  Queue in = {NULL, NULL};
  Queue out {NULL, NULL};
  Stack tree = {NULL};
  
  bool run = true;
  
  char input[99] = "";

  const char* QUIT = "QUIT";
  const char* IN = "INFIX";
  const char* POST = "POSTFIX";
  const char* PRE = "PREFIX";
  
  while (run == true) {

    cout << "Enter expression: ";
    cin.getline(input, 99);
    
    if (strcmp(input, "QUIT") == 0) {
      run = false;
    } else {

      // Process input
      
      in = createQueue(input);
      out = ShuntYard(in);
      tree = createTree(out);

      // Print expression
      
      cout << "Enter format: ";
      cin.getline(input, 99);
      cout << endl;

      if (strcmp(input, PRE) == 0) {
	print(tree.peek(), 1);
      } else if (strcmp(input, IN) == 0) {
	print(tree.peek(), 2);
      } else if (strcmp(input, POST) == 0) {
	print(tree.peek(), 3);
      }
      
      cout << endl;
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

      // Pop operators to queue if order is higher
      
      while (s.peek() != NULL &&
	  node->getOrder() <= s.peek()->getOrder()) {
	// Do not pop if not left associative and equal
	if (s.peek()->isLeft() ||
	    node->getOrder() != s.peek()->getOrder()) {
	  out.enqueue(s.pop());
	}
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

Stack createTree(Queue in) {
  Stack s = {NULL};

  while (in.front != NULL) {
    Node * node = in.front;
    in.dequeue();

    if (node->isNum()) { // Add num to stack
      s.push(node);
    } else { // Pop num to leafs of operator tree
      node->right = s.pop();
      node->left = s.pop();

      s.push(node);
    }
  }

  return s;
}

void print(Node* node, int n) {

  Node* left = node->left;
  Node* right = node->right;

  if (n == 1) {
    cout << node->token;
  }
  
  if (left != NULL) {
    print(left, n);
  }

  if (n == 2) {
    cout << node->token;
  }
    
  if (right != NULL) {
    print(right, n);
  }

  if (n == 3) {
    cout << node->token;
  }

  delete node;
  node = NULL;
}
