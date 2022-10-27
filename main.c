#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
    char element[10];
    struct node *next;
} stack;

stack *operator;
stack *postfix;
stack *post_top;
stack *op_top;

int a = 0, k = 0;

void operatorStack() {
    stack *iter;
    iter = operator;

    if (operator == NULL)
        printf("\t\t");
    else {
        while (iter != NULL) {
            printf("%c", iter->element[0]);
            iter = iter->next;
        }
        printf("\t\t");
    }
}

void postfixStack() {
    stack *iter;
    iter = postfix;
    char i;

    if (postfix == NULL)
        printf("\t\t");
    else {
        while (iter != NULL) {
            i = 0;
            while (iter->element[i] >= '0' && iter->element[i] <= '9') {
                printf("%c", iter->element[i]);
                i++;
            }
            if (iter->element[0] < '0' || iter->element[0] > '9') {
                printf("%c", iter->element[0]);
            }
            iter = iter->next;
        }
        printf("\t\t");
    }
}

void push(char x) {
    stack *temp;

    if (x >= '0' && x <= '9') {
        if (k != 0) {
            post_top->element[k] = x;
            return;
        }
        temp = (stack *) calloc(1, sizeof(stack *));
        if (postfix == NULL) {
            temp->element[0] = x;
            temp->next = NULL;
            postfix = temp;
            post_top = postfix;
        } else {
            temp->element[0] = x;
            temp->next = NULL;
            post_top->next = temp;
            post_top = post_top->next;
        }
    } else {
        temp = (stack *) calloc(1, sizeof(stack *));
        if (a == 1) {
            temp->element[0] = x;
            temp->next = NULL;
            post_top->next = temp;
            post_top = post_top->next;
        } else {
            if (operator == NULL) {
                temp->element[0] = x;
                temp->next = NULL;
                operator = temp;
                op_top = operator;
            } else {
                temp->element[0] = x;
                temp->next = NULL;
                op_top->next = temp;
                op_top = op_top->next;
            }
        }
    }
}

void pop() {
    stack *temp;
    a = 0;

    if (op_top->element[0] != '(' && op_top->element[0] != ')') {
        a = 1;
        push(op_top->element[0]);
    }

    if (op_top == operator) {
        operator = NULL;
        op_top = NULL;
    }
    temp = operator;

    if (temp != NULL) {
        while (temp->next != NULL) {
            if (temp->next->next == NULL) {
                temp->next = NULL;
                op_top = temp;
                break;
            }
            temp = temp->next;
        }
    }
}

int priority(char c) {
    if (c == '^') return 3;
    else if (c == '/' || c == '*') return 2;
    else if (c == '+' || c == '-') return 1;
    else if (c == '(') return 0;
    else return -1;
}

void control(char y) {
    a = 0;
    if (operator == NULL) {
        push(y);
        return;
    }
    if (priority(y) == -1) {
        while (op_top->element[0] != '(')
            pop();
    }
    if (priority(op_top->element[0]) < priority(y))
        push(y);
    else if (priority(op_top->element[0]) >= priority(y)) {
        if (y == '(')
            push(y);
        else
            pop();
    }
}

void writer() {
    operatorStack();
    postfixStack();
    printf("\n");
}

int solve(int b, int n, char m) {
    switch (m) {
        case '+' :
            return b + n;
        case '-' :
            return b - n;
        case '*' :
            return b * n;
        case '/' :
            return b / n;
        case '^' :
            return pow(b, n);
    }
}

void solution() {
    stack *variable_a, *variable_b, *variable_c, *temp;
    int n1 = 0, n2 = 0, v = 0, value, count = 0, cou = 0, z, value2, value3;
    temp = (stack *) calloc(1, sizeof(stack *));

    variable_a = variable_b = variable_c = postfix;

    for (int i = 0; i < 2; ++i)
        variable_a = variable_a->next;

    while (variable_a != NULL) {
        if (variable_a->element[0] < '0' || variable_a->element[0] > '9') {
            for (int i = 9; i >= 0; i--) {
                if (variable_b->element[i] < '0' || variable_b->element[i] > '9')
                    continue;
                if (cou == 0)
                    n1 = n1 + (10 * cou + ((int) variable_b->element[i] - 48));
                else
                    n1 = n1 + (pow(10, cou) * ((int) variable_b->element[i] - 48));
                cou++;
            }
            cou = 0;
            for (int i = 9; i >= 0; i--) {
                if (variable_b->next->element[i] < '0' || variable_b->next->element[i] > '9')
                    continue;
                if (cou == 0)
                    n2 = n2 + (10 * cou + ((int) variable_b->next->element[i] - 48));
                else
                    n2 = n2 + (pow(10, cou) * ((int) variable_b->next->element[i] - 48));
                cou++;
            }
            value = solve(n1, n2, variable_a->element[0]);
            value2 = value3 = value;

            char array[10];
            for (int i = 0; i < 10; ++i)
                array[i] = 0;

            while (value != 0) {
                value /= 10;
                v++;
            }
            for (int i = 0; i < v; ++i) {
                z = value2 % 10;
                z += 48;
                array[v - i - 1] = z;
                value2 = value2 / 10;
            }
            strcpy(temp->element, array);

            if (variable_b == postfix) {
                temp->next = variable_a->next;
                postfix = temp;
                printf("%d\t     %c     \t%d  \t     %d\t     ", n1, variable_a->element[0], n2, value3);
                free(variable_a);
                free(variable_b->next);
                free(variable_b);
                return;
            } else {
                temp->next = variable_a->next;
                variable_c->next = temp;
                printf("%d\t     %c     \t%d  \t     %d\t     ", n1, variable_a->element[0], n2, value3);
                free(variable_a);
                free(variable_b->next);
                free(variable_b);
                return;
            }
        }
        if (count >= 1)
            variable_c = variable_c->next;
        variable_b = variable_b->next;
        variable_a = variable_a->next;
        count++;
    }
}

int main() {
    char eps[100];
    printf("Expression -> ");
    scanf("%s", eps);
    printf("-Input-\t         -Process-     -operator stack-     -postfix-\n");

    for (int i = 0; i < strlen(eps); i++) {
        while (1) {
            printf("%s\t\t", eps);
            printf("%c\t\t", eps[i]);
            if (eps[i] >= '0' && eps[i] <= '9') {
                if (eps[i - 1] >= '0' && eps[i - 1] <= '9') k++;
                push(eps[i]);
                writer();
                break;
            } else {
                k = 0;
                control(eps[i]);
                writer();
                if (a == 0)
                    break;
            }
        }
    }
    while (operator != NULL) {
        pop();
        printf("%s\t\t", eps);
        printf("\t\t");
        writer();
    }
    printf("\n\n\nNumber-1  Operator    Number-2     Result    New-Input\n");
    while (postfix->next != NULL) {
        solution();
        postfixStack();
        printf("\n");
    }
    getchar();
    getchar();
}
