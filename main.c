#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct node {
    float data;
    struct node* next;
};
typedef struct node node;

node* newNode(float value) {
    node* n = malloc(sizeof(node));
    n->data = value;
    n->next = NULL;
    return n;
}

typedef struct {
    node* head;
} stack;

stack* initialize() {
    stack* s = malloc(sizeof(stack));
    s->head = NULL;
    return s;
}

void push(stack* s, float value) {
    node* n = newNode(value);
    if (!s->head) {
        s->head = n;
    } else {
        n->next = s->head;
        s->head = n;
    }
}
#define empty 0
float pop(stack* s) {
    if (!s->head) {
        printf("stack is empty\n");
        return empty;
    }
    node* temp = s->head;
    s->head = temp->next;
    float x =temp->data;
    free(temp);
    return x;
}

float peek(stack* s) {
    if (!s->head) {
        return empty;
    }
    return s->head->data;
}

int isEmpty(stack* s) {
    return s->head == NULL;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int precedence(char c) {
    switch (c) {

        case '(':
               return 4;
        case '^':
            return 3;
        case '*':
        case '/':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

char* infixToPostfix(char* infix) {
    stack* s = initialize();
    char* postfix = malloc(strlen(infix)*2); *postfix='\0';
    char* token = strtok(infix, " ");
    while (token) {
        if (isdigit(*token) || (*token == '-' && isdigit(token[1]))) {
            strcat(postfix, token);
            strcat(postfix, " ");
            }
        else if (*token == '(') {
            push(s, (float)*token);
            }
        else if (*token == ')') {
            while (!isEmpty(s) && (char)peek(s) != '(') {
                char c[2];
                c[0]=(char)pop(s);
                c[1]='\0';
                strcat(postfix, c);
                strcat(postfix, " ");
            }
            pop(s);
            }
            else if(isOperator(*token) &&(isEmpty(s)||(char)peek(s)=='(')){
                 push(s, (float)token[0]);
                 }

         else if (isOperator(*token)) {
            while (!isEmpty(s) && precedence((char)peek(s)) >= precedence(*token)) {
                char c[2];
                c[0]=(char)pop(s);
                c[1]='\0';
                strcat(postfix, c);
                strcat(postfix, " ");
            }
            push(s, (float)*token);
        }
        token = strtok(NULL, " ");
    }
    while (!isEmpty(s)) {
        char c[2];
        c[0]=(char)pop(s);
        c[1]='\0';
        strcat(postfix, c);
        strcat(postfix, " ");
    }
    return postfix;
}
float operate( float x1, float x2, char c){
    switch(c){
        case('*'): return x1*x2;
        case('/'): return x1/x2;
        case('^'):return (float)pow(x1,x2);
        case('%'): return (int)x1%(int)x2;
        case('+'): return x1+x2;
        case('-'): return x1-x2;
    }
}
float evaluate(char*postfix){
    stack*s = initialize();
    char*tok = strtok(postfix," ");
    while(tok){
        if(isdigit(*tok) || (*tok == '-' && isdigit(tok[1]))){
            push(s, atof(tok));
        }
        else{
            float x2=pop(s);
            float x1=pop(s);
            float result = operate(x1,x2,tok[0]);
            push(s, result);
        }
        tok=strtok(NULL, " ");
    }
    float result = pop(s);
    return result;
}
int main() {

    printf("please, enter an infix question with spaces between inputs :)\n? ");
    char infix[200];
    gets(infix);
    char* postfix;

    postfix=infixToPostfix(infix);
    printf("\n\nPostfix expression: %s\n", postfix);
    float result=evaluate(postfix);
    printf("= %f\n",result);



return 0;
}
