#include "stack.h"

struct stack *initStack() {
    struct stack *stack = malloc(sizeof(struct stack));
    if (stack != NULL) {
        stack->top = NULL;
    }
    return stack;
}

struct stackNode *initStackNode(int id, double val) {
    struct stackNode *new_stack = malloc(sizeof(struct stackNode));

    new_stack->id = id;
    new_stack->value = val;
    new_stack->next = NULL;

    return new_stack;
}

void push(struct stack *stack, int id, double val) {
    struct stackNode *new_stack_node = initStackNode(id, val);
    if (stack != NULL) {
        new_stack_node->next = stack->top;
        stack->top = new_stack_node;
    }
}

void pop(struct stack *stack, int *id, double *val) {
    if (stack->top) {
        struct stackNode *remove = stack->top;
        *id = stack->top->id;
        *val = stack->top->value;
        stack->top = stack->top->next;
        free(remove);
    }
}

void destroyStack(struct stack *stack) {
    while (stack->top) {
        int id;
        double val;
        pop(stack, &id, &val);
    }
    free(stack);
}

struct queue *initQue() {
    struct queue *que = malloc(sizeof(struct queue));
    if (que != NULL) {
        que->head = NULL;
    }
    return que;
}

struct queueNode *initQueNode(int id, double val) {
    struct queueNode *que_node = malloc(sizeof(struct queueNode));
    if (que_node != NULL) {
        que_node->id = id;
        que_node->value = val;
        que_node->next = NULL;
    }
    return que_node;
}

struct queue *add_que(struct queue *que, int id, double val) {
    struct queueNode *node = initQueNode(id, val);
    if (que->head == NULL) {
        que->head = node;
        que->tail = node;
    } else {
        que->tail->next = node;
        que->tail = node;
    }
    return que;
}

void takeFromQueue(struct queue *que, int *id, double *val) {
    if (que->head) {
        *id = que->head->id;
        *val = que->head->value;
        struct queueNode *node = que->head->next;
        free(que->head);
        que->head = node;
    }
}

void destroyQue(struct queue *que) {
    struct queueNode *node = que->head;
    while (que->head) {
        que->head = que->head->next;
        free(node);
        node = que->head;
    }
    free(que);
}

struct queue *copyQue(struct queue *que) {
    struct queue *que_cp = initQue();
    struct queueNode *node = que->head;
    while (node) {
        add_que(que_cp, node->id, node->value);
        node = node->next;
    }
    return que_cp;
}
