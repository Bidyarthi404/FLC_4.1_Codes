#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* input;
int pos = 0;

void Exp();
void Term();
void Factor();
void ID();
void NUM();
void match(char expected);
void error();

void Exp() {
    Term();
    while (input[pos] == '+' || input[pos] == '-') {
        pos++;
        Term();
    }
}

void Term() {
    Factor();
    while (input[pos] == '*' || input[pos] == '/') {
        pos++;
        Factor();
    }
}

void Factor() {
    if (input[pos] == '(') {
        match('(');
        Exp();
        match(')');
    } else if (isalpha(input[pos])) {
        ID();
    } else if (isdigit(input[pos])) {
        NUM();
    } else {
        error();
    }
}

void ID() {
    if (input[pos] >= 'a' && input[pos] <= 'e') {
        pos++;
    } else {
        error();
    }
}

void NUM() {
    if (isdigit(input[pos])) {
        pos++;
    } else {
        error();
    }
}

void match(char expected) {
    if (input[pos] == expected) {
        pos++;
    } else {
        error();
    }
}

void error() {
    printf("Error parsing at position %d: %c\n", pos, input[pos]);
    exit(1);
}

int main() {
    input = (char*)malloc(1024 * sizeof(char));
    if (input == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter an expression: ");
    scanf("%1023s", input);
    Exp();

    if (input[pos] == '\0') {
        printf("The input string is a valid arithmetic expression.\n");
    } else {
        error();
    }

    free(input);
    return 0;
}
