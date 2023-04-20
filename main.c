#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

char stack[MAX_SIZE];
int top = -1;

bool isFull() { return top == MAX_SIZE - 1; }

bool isEmpty() { return top == -1; }

void push(char x) {
    if (isFull()) {
        printf("the stack is full\n");
        exit(1);
    }
    stack[++top] = x;
}

char pop() {
    if (isEmpty()) {
        printf("the stack is empty\n");
        exit(1);
    }
    return stack[top--];
}

typedef struct node {
    char *data;
    struct node *next;
} node;

void addNode(node **head, char *data) {
    node *newNode = malloc(sizeof(node));
    newNode->data = malloc(strlen(data));
    strcpy(newNode->data, data);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        node *current = *head;
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
    else
        return 0;
}

void infixToPostfix(node *head, char string[]) {
    int i = 0;
    while (head != NULL) {
        if (isalnum(*head->data) || (*head->data == '-' && strlen(head->data) > 1)) {
            for (int j = 0; j < strlen(head->data); j++) {
                string[i++] = head->data[j];
            }
            string[i++] = ' ';
        } else if (*head->data == '(') {
            push(*head->data);
        } else if (*head->data == ')') {
            while (stack[top] != '(') {
                string[i++] = pop();
                string[i++] = ' ';
            }
            pop();
        } else {
            while (!isEmpty() && precedence(*head->data) <= precedence(stack[top])) {
                string[i++] = pop();
                string[i++] = ' ';
            }
            push(*head->data);
        }
        head = head->next;
    }
    while (!isEmpty()) {
        string[i++] = pop();
        string[i++] = ' ';
    }
    string[i] = '\0';
}

int main() {
    node *head = NULL;
    char input[MAX_SIZE];
    char output[MAX_SIZE];
    char tempString[MAX_SIZE];

    printf("Input: ");
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

    printf("Output: %s\n", output);
    return 0;
}
