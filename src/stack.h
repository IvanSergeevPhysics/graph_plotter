#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

struct stackNode {
    int id;
    double value;
    struct stackNode* next;
};

struct stack {
    struct stackNode* top;
};

struct queue {
    struct queueNode* head;
    struct queueNode* tail;
};

struct queueNode {
    int id;
    double value;
    struct queueNode* next;
};

struct stack* initStack();
struct stackNode* initStackNode(int id, double val);
void push(struct stack* stack, int id, double val);
void pop(struct stack* stack, int* id, double* val);
void destroyStack(struct stack* stack);

struct queue* initQue();
struct queueNode* initQueNode(int id, double val);
struct queue* add_que(struct queue* que, int id, double val);
struct queue* copyQue(struct queue* que);
void takeFromQueue(struct queue* que, int* id, double* val);
void destroyQue(struct queue* que);

#endif