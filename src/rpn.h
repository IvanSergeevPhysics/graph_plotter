#ifndef RPN_H
#define RPN_H

#include "parse.h"
#include "stack.h"

int priority(int id);
int isFuctionOrOperator(int id);
int isDigitOrX(int id);
void revPolNotStep(struct queue* out, struct stack* stack, int id, int val);
void closeBracket(struct stack* stack, struct queue* out);
void checkPriority(struct stack* stack, struct queue* out, int id);
void rpn(struct queue* out, struct queue* in);

#endif