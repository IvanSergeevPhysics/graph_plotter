#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculations.h"
#include "defines.h"
#include "parse.h"
#include "rpn.h"
#include "stack.h"

#define POINTS 300

char* input();
void plot(struct queue* out, double a, double b);
void getGraph();

int main() { getGraph(); }

char* input(double* a, double* b) {
    printf("Enter graph limits: ");
    scanf("%lf%lf", a, b);
    char* string = (char*)malloc(sizeof(char));
    getchar();
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
    if (strlen(string) == 0) {
        printf("Error: invalid input\n");
        exit(0);
    }
    return string;
}

void plot(struct queue* out, double a, double b) {
     struct queue* out_cp = copyQue(out);
     double h = (b-a)/POINTS;
     FILE *fp;
     if((fp = fopen("nodes.txt", "w"))){
     	for (int i = 0; i < POINTS; i++){
		struct queue* out_cp = copyQue(out);
     		double res = calculate(out_cp, a+(double)i*h);
		fprintf(fp, "%lf %lf\n", a+(double)i*h, res);
        	destroyQue(out_cp);
     	}
	fclose(fp);
     }
    
}

void getGraph() {
    double a, b;
    char* st = input(&a, &b);
    struct queue* que = initQue();
    parsing(st, que);
    if (!checkBraces(que)) {
        printf("Error: invalid input\n");
        exit(0);
    }
    struct queue* out = initQue();
    rpn(out, que);
    plot(out, a, b);
    destroyQue(que);
    destroyQue(out);
    free(st);
    system("python graph_plotter.py");
}