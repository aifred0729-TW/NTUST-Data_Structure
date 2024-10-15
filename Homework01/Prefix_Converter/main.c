#pragma warning(disable:4996)

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100 /*maximuTn stack size */
#define MAX_EXPR_SIZE 100 /*max size of expression */

char expr[] = "a*(b+c)/d-g";
int index = 0;

typedef enum {
    lparen,
    rparen,
    plus,
    minus,
    divide,
    times,
    mod,
    eos,
    operand
} precedence;

precedence get_token(char* symbol, int* n) {
    *symbol = expr[(*n)++];
    switch (*symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    case '%': return mod;
    case '\0': return eos;
    default: return operand;
    }
}

void print_token(precedence token) {
    switch (token) {
    case lparen: printf("("); break;
    case rparen: printf(")"); break;
    case plus: printf("+"); break;
    case minus: printf("-"); break;
    case times: printf("*"); break;
    case divide: printf("/"); break;
    case mod: printf("%"); break;
    case eos: printf("eos"); break;
    case operand: printf("operand"); break;
    }
}

precedence stack[MAX_STACK_SIZE];
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

precedence delete(int* top) {
    if (*top == -1) return eos;
    return stack[(*top)--];
}

void add(int* top, precedence token) {
    stack[++(*top)] = token;
}

void postfix() {
    char symbol;
    precedence token;
    int n = 0;
    int top = 0;
    stack[0] = eos;

    for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n)) {
        if (token == operand) {
            printf("%c", symbol);
        }
        else if (token == rparen) {
            while (stack[top] != lparen) {
                print_token(delete(&top));
            }
            delete(&top);
        }
        else {
            while (isp[stack[top]] >= icp[token]) {
                print_token(delete(&top));
            }
            add(&top, token);
        }
    }
    while ((token = delete(&top)) != eos) {
        print_token(token);
    }
    printf("\n");
}

void prefixConverter() {

    strrev(expr);

    for (size_t i = 0; i < strlen(expr); i++) {
        if (expr[i] == ')') expr[i] = '(';
        else if (expr[i] == '(') expr[i] = ')';
    }

    char symbol;
    precedence token;
    int n = 0;
    int top = 0;
    stack[0] = eos;

    for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n)) {
        if (token == operand) {
            printf("%c", symbol);
        }
        else if (token == rparen) {
            while (stack[top] != lparen) {
                print_token(delete(&top));
            }
            delete(&top);
        }
        else {
            while (isp[stack[top]] > icp[token]) {
                print_token(delete(&top));
            }
            add(&top, token);
        }
    }
    while ((token = delete(&top)) != eos) {
        print_token(token);
    }
    printf("\n");
}

int main() {


    postfix();
    prefixConverter();


    return 0;
}