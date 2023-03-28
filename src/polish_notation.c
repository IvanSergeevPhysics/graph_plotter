#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculations.h"
#include "parse.h"
#include "rpn.h"
#include "stack.h"

#define HEIGHT 25
#define WIDTH 80
#define PI 3.14159265358

char* input();
void plot(struct queue* out);

int main() {
    char* st = input();
    struct queue* que = initQue();
    parsing(st, que);
    struct queue* out = initQue();
    rpn(out, que);
    plot(out);
    destroyQue(que);
    destroyQue(out);
    free(st);
}

char* input() {
    char* string = (char*)malloc(sizeof(char));
    int c = getchar();
    int i = 0;
    while (c != EOF && c != '\n') {
        char* new = (char*)realloc(string, sizeof(char) * (i + 2));
        if (new == NULL) {
            free(string);
        } else {
            string[i] = c;
            c = getchar();
            i++;
        }
    }
    string[i] = 0;
    return string;
}

void plot(struct queue* out) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            struct queue* out_cp = copyQue(out);
            int res = -calculate(out_cp, (double)(j * 4 * PI / WIDTH)) * HEIGHT / 2 + 13;
            if (i == res)
                printf("*");
            else
                printf(".");
            destroyQue(out_cp);
        }
        printf("\n");
    }
}
