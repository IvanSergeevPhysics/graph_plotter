#include "calculations.h"

#include "rpn.h"

double getUnar(int id, double a) {
    double (*actions[7])(double) = {sin, cos, tan, ctg, sqrt, log, minus};
    return actions[id - SIN](a);
}

double getBinar(int id, double a, double b) {
    double (*actions[4])(double a, double b) = {sum, sub, mul, cDiv};
    return actions[id - SUM](a, b);
}

double minus(double a) { return -a; }

double ctg(double a) { return 1.0 / tan(a); }

double sum(double a, double b) { return a + b; }

double sub(double a, double b) { return a - b; }

double mul(double a, double b) { return a * b; }

double cDiv(double a, double b) { return a / b; }

int isBinary(int id) {
    int flag = 0;
    if (id == SUM || id == SUB || id == MUL || id == DIV) flag = 1;
    return flag;
}

int isUnary(int id) {
    int flag = 0;
    if (id == SIN || id == COS || id == TG || id == LN)
        flag = 1;
    else if (id == SQRT || id == CTG || id == U_M)
        flag = 1;

    return flag;
}

void calculateStep(struct queue* out, struct stack* stack, double x) {
    int id;
    double val;
    takeFromQueue(out, &id, &val);
    if (id == NUM)
        push(stack, id, val);
    else if (id == X)
        push(stack, id, x);
    else if (isBinary(id)) {
        int id_a, id_b;
        double val_a, val_b;
        pop(stack, &id_b, &val_b);
        pop(stack, &id_a, &val_a);
        double result = getBinar(id, val_a, val_b);
        push(stack, id_a, result);
    } else if (isUnary(id)) {
        int id_a;
        double val_a;
        pop(stack, &id_a, &val_a);
        double result = getUnar(id, val_a);
        push(stack, id_a, result);
    }
}

double calculate(struct queue* out, double x) {
    struct stack* stack = initStack();
    while (out->head) {
        calculateStep(out, stack, x);
    }
    double result = stack->top->value;
    destroyStack(stack);
    return result;
}