#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <math.h>

#include "defines.h"
#include "stack.h"

double calculate(struct queue* out, double x);
double getUnar(int id, double a);
double getDinar(int id, double a, double b);
double cDiv(double a, double b);
double mul(double a, double b);
double sub(double a, double b);
double sum(double a, double b);
double ctg(double a);
double minus(double a);

int isUnary(int id);
int isBinary(int id);

void calculateStep(struct queue* out, struct stack* stack, double x);

#endif