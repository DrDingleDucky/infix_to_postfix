#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 256

char charStack[MAX_SIZE];
int count = 0;

void push(char x)
{
    if (count == MAX_SIZE)
    {
        printf("there is not space left in the char stack\n");
        exit(1);
    }
    charStack[count] = x;
    count++;
}

char pop()
{
    if (count == 0)
    {
        fprintf(stderr, "nothing to take from the char stack\n");
        exit(1);
    }
    char result = charStack[count - 1];
    count--;
    return result;
}

void removeSpaces(char string[])
{
    int i, j;
    for (i = 0, j = 0; i < strlen(string); i++)
    {
        if (string[i] != ' ')
        {
            string[j++] = string[i];
        }
    }
    string[j] = '\0';
}

int precedence(char operator)
{
    if (operator== '+' || operator== '-')
    {
        return 1;
    }
    else if (operator== '*' || operator== '/')
    {
        return 2;
    }
    else if (operator== '^')
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

void infixToPostfix(char inputString[], char outputString[])
{
    char token;
    int i, j;
    for (i = 0, j = 0; i < strlen(inputString); i++)
    {
        token = inputString[i];

        if (isalnum(token))
        {
            outputString[j++] = token;
        }
        else if (token == '(')
        {
            push(token);
        }
        else if (token == ')')
        {
            while (charStack[count - 1] != '(')
            {
                outputString[j++] = pop();
            }
            pop();
        }
        else
        {
            while (count != 0 && precedence(token) <= precedence(charStack[count - 1]))
            {
                outputString[j++] = pop();
            }
            push(token);
        }
    }
    while (count != 0)
    {
        outputString[j++] = pop();
    }
    outputString[j] = '\0';
}

int main()
{
    char inputString[MAX_SIZE];
    char outputString[MAX_SIZE];

    printf("enter a equation: ");
    fgets(inputString, MAX_SIZE, stdin);

    removeSpaces(inputString);

    printf("input: %s", inputString);

    infixToPostfix(inputString, outputString);

    printf("output: %s", outputString);
    return 0;
}
