#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

char stack[MAX_SIZE];
int top = 0;

bool isFull() { return top == MAX_SIZE; }

bool isEmpty() { return top == -1; }

void push(char x) {
  if (isFull()) {
    printf("there is not space left in the stack\n");
    exit(1);
  }
  stack[top++] = x;
}

char pop() {
  if (isEmpty()) {
    printf("nothing to take from the stack\n");
    exit(1);
  }
  char result = stack[--top];
  return result;
}

struct Node {
  char *data;
  struct Node *next;
};

void addNode(struct Node **head, char *newData) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = strdup(newData);
  newNode->next = NULL;

  if (*head == NULL) {
    *head = newNode;
  } else {
    struct Node *current = *head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
}

int precedence(char operator) {
  if (operator== '+' || operator== '-')
    return 1;
  else if (operator== '*' || operator== '/')
    return 2;
  else if (operator== '^')
    return 3;
  else
    return 0;
}

void infixToPostfix(struct Node *head, char string[]) {
  struct Node *current = head;
  int i = 0;

  while (current != NULL) {
    if (isalnum(*current->data) ||
        current->data[0] == '-' && strlen(current->data) != 1) {
      for (int j = 0; j < strlen(current->data); j++) {
        string[i++] = current->data[j];
      }
      string[i++] = ' ';
    } else if (*current->data == '(') {
      push(*current->data);
    } else if (*current->data == ')') {
      while (stack[top - 1] != '(') {
        string[i++] = pop();
        string[i++] = ' ';
      }
      pop();
    } else {
      while (top != 0 &&
             precedence(*current->data) <= precedence(stack[top - 1])) {
        string[i++] = pop();
        string[i++] = ' ';
      }
      push(*current->data);
    }
    current = current->next;
  }
  while (top != 0) {
    string[i++] = pop();
    string[i++] = ' ';
  }
  string[i] = '\0';
}

int main() {
  struct Node *head = NULL;
  char input[MAX_SIZE];
  char output[MAX_SIZE];

  char tempString[16];

  printf("input: ");
  fgets(input, MAX_SIZE, stdin);

  int i = 0;
  int j = 0;
  while (input[i] != '\0') {
    if (isspace(input[i])) {
      tempString[j++] = '\0';
      addNode(&head, tempString);
      j = 0;
    } else {
      tempString[j++] = input[i];
    }
    i++;
  }

  infixToPostfix(head, output);

  printf("output: %s\n", output);
  return 0;
}
