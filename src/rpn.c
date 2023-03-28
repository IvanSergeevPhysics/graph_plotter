#include "rpn.h"

#include "stack.h"

int priority(int id) {
    int flag = -1;
    if (id == SUM || id == SUB)
        flag = 1;
    else if (id == MUL || id == DIV)
        flag = 2;
    else if (id == U_M)
        flag = 3;
    else if (id == SIN || id == COS)
        flag = 4;
    else if (id == TG || id == CTG)
        flag = 4;
    else if (id == SQRT || id == LN)
        flag = 4;
    else if (id == O_B)
        flag = 5;

    return flag;
}

int isFuctionOrOperator(int id) {
    int flag = -1;

    if (id == SIN || id == COS || id == TG)
        flag = 1;
    else if (id == SQRT || id == LN || id == CTG)
        flag = 1;
    else if (id == SUM || id == SUB || id == MUL)
        flag = 1;
    else if (id == DIV || id == U_M || id == O_B)
        flag = 1;

    return flag;
}

void closeBracket(struct stack* stack, struct queue* out) {
    int id;
    double val;
    pop(stack, &id, &val);
    while (stack->top && id != O_B) {
        add_que(out, id, val);
        pop(stack, &id, &val);
    }
}

void checkPriority(struct stack* stack, struct queue* out, int id) {
    while (stack->top && stack->top->id != O_B && priority(stack->top->id) >= priority(id)) {
        int loc_id;
        double loc_val;
        pop(stack, &loc_id, &loc_val);
        add_que(out, loc_id, loc_val);
    }
}

int isDigitOrX(int id) {
    int flag = 0;
    if (id == NUM || id == X) flag = 1;
    return flag;
}

void revPolNotStep(struct queue* out, struct stack* stack, int id, int val) {
    if (isDigitOrX(id))
        add_que(out, id, val);
    else if (id == C_B)
        closeBracket(stack, out);
    else if (isFuctionOrOperator(id)) {
        checkPriority(stack, out, id);
        push(stack, id, val);
    } else
        printf("Error: RPN crush\n");
}

void rpn(struct queue* out, struct queue* in) {
    int id;
    double val;
    struct stack* stack = initStack();
    while (in->head) {
        takeFromQueue(in, &id, &val);
        revPolNotStep(out, stack, id, val);
    }
    while (stack->top) {
        pop(stack, &id, &val);
        add_que(out, id, val);
    }

    destroyStack(stack);
}
