#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 256

char stack[MAX_SIZE];
int top = 0;

bool isFull()
{
    return top == MAX_SIZE;
}

bool isEmpty()
{
    return top == -1;
}

void push(char x)
{
    if (isFull())
    {
        printf("there is not space left in the stack\n");
        exit(1);
    }
    stack[top++] = x;
}

char pop()
{
    if (isEmpty())
    {
        printf("nothing to take from the stack\n");
        exit(1);
    }
    char result = stack[--top];
    return result;
}

struct Node
{
    char *data;
    struct Node *next;
};

void addNode(struct Node **head, char *newData)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = strdup(newData);
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct Node *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

int precedence(char operator)
{
    if (operator== '+' || operator== '-')
        return 1;
    else if (operator== '*' || operator== '/')
        return 2;
    else if (operator== '^')
        return 3;
    else
        return 0;
}

char infixToPostfix(struct Node *head, char string[])
{
    struct Node *current = head;
    int i = 0;
    while (string[i] != '\n')
    {
        printf("yes: %s\n", string[i]);
    }

    int i = 0;
    while (current != NULL)
    {
        printf("%s\n", current->data);
        if (isalnum(*current->data))
        {
            for (int j = 0; j < strlen(current->data); j++)
            {
                string[i++] = current->data[j];
            }
            string[i++] = ' ';
        }
        else if (*current->data == '(')
        {
            push(*current->data);
        }
        else if (*current->data == ')')
        {
            while (stack[top - 1] != '(')
            {
                string[i++] = pop();
                string[i++] = ' ';
            }
            pop();
        }
        else
        {
            while (top != 0 && precedence(*current->data) <= precedence(stack[top - 1]))
            {
                string[i++] = pop();
                string[i++] = ' ';
            }
            push(*current->data);
        }
        current = current->next;
    }
    while (top != 0)
    {
        string[i++] = pop();
        string[i++] = ' ';
    }
    string[--i] = '\0';
    return *string;
}

int main()
{
    struct Node *head = NULL;
    char inputString[] = "12 + 34";
    char outputString[MAX_SIZE];

    outputString = infixToPostfix(head, inputString);

    printf("output: %s\n", outputString);
    return 0;
}
