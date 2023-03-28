#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <string.h>

#include "defines.h"
#include "stack.h"

void parsing(char* str, struct queue* que);
int parsingStep(char* str, int i, struct queue* que);
int checkBraces(struct queue* que);
int fuctions(char* str);
int fuctionsLen(int id);

int is_sin(char* str);
int is_cos(char* str);
int is_tg(char* str);
int is_ctg(char* str);
int is_sqrt(char* str);
int is_ln(char* str);

int is_digit(char str);
int d_len(char* str);
int is_x(char str);
int operator(char str);

#endif