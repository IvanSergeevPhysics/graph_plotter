#include "parse.h"

int is_sin(char *str) { return !strncmp(str, "sin(", SIN_LEN + 1); }
int is_cos(char *str) { return !strncmp(str, "cos(", COS_LEN + 1); }
int is_tg(char *str) { return !strncmp(str, "tan(", TG_LEN + 1); }
int is_ctg(char *str) { return !strncmp(str, "ctg(", CTG_LEN + 1); }
int is_sqrt(char *str) { return !strncmp(str, "sqrt(", SQRT_LEN + 1); }
int is_ln(char *str) { return !strncmp(str, "ln(", LN_LEN + 1); }

int is_digit(char str) { return str >= '0' && str <= '9'; }
int is_x(char str) { return str == 'x' || str == 'X'; }

int d_len(char *str) {
    int digit = 0;
    int i = 0;
    while (is_digit(str[i]) || (str[i] == '.' && !digit)) {
        if (str[i] == '.') digit = 1;
        i++;
    }
    return i;
}

int fuctions(char *str) {
    int flag = -1;
    if (is_sin(str))
        flag = SIN;
    else if (is_cos(str))
        flag = COS;
    else if (is_tg(str))
        flag = TG;
    else if (is_ctg(str))
        flag = CTG;
    else if (is_sqrt(str))
        flag = SQRT;
    else if (is_ln(str))
        flag = LN;

    return flag;
}

int fuctionsLen(int id) {
    int len = 0;
    if (id == SIN)
        len = SIN_LEN;
    else if (id == COS)
        len = COS_LEN;
    else if (id == TG)
        len = TG_LEN;
    else if (id == CTG)
        len = CTG_LEN;
    else if (id == SQRT)
        len = SQRT_LEN;
    else if (id == LN)
        len = LN_LEN;

    return len - 1;
}

int operator(char str) {
    int flag = -1;
    if (str == '+')
        flag = SUM;
    else if (str == '-')
        flag = SUB;
    else if (str == '*')
        flag = MUL;
    else if (str == '/')
        flag = DIV;
    else if (str == '(')
        flag = O_B;
    else if (str == ')')
        flag = C_B;

    return flag;
}

int parsingStep(char *str, int i, struct queue *que) {
    static int minus;
    if (i == 0) minus = 1;

    if (is_digit(str[i])) {
        double val = 0;
        sscanf(str + i, "%lf", &val);
        int len = d_len(str + i);
        i = i + len - 1;
        add_que(que, NUM, val);
        minus = 0;
    } else if (str[i] == '-' && minus){
        add_que(que, U_M, 0);
	minus = 0;
    }
    else if (operator(str[i]) != -1) {
        add_que(que, operator(str[i]), 0);
        minus = 1;
    } else if (fuctions(str + i) != -1) {
        add_que(que, fuctions(str + i), 0);
        add_que(que, O_B, 0);
        i += fuctionsLen(fuctions(str + i)) + 1;
        minus = 1;
    } else if (is_x(str[i])) {
        add_que(que, X, 0);
    } else
        i = -1;

    return i;
}

void parsing(char *str, struct queue *que) {
    int i = 0;
    while (str[i] != '\0') {
        i = parsingStep(str, i, que);
        if (i < 0) {
            printf("Error: invalid input\n");
            exit(0);
        }
        i++;
    }
}

int checkBraces(struct queue *que) {
    int flag = 1;
    struct stack *braces = initStack();
    struct queueNode *tmp = que->head;
    int id;
    double val;
    while (tmp) {
        if (tmp->id == O_B)
            push(braces, C_B, 0);
        else if (braces->top && tmp->id == C_B)
            pop(braces, &id, &val);
        else if (!(braces->top) && tmp->id == C_B)
            flag = 0;
        tmp = tmp->next;
    }
    if (braces->top) flag = 0;
    destroyStack(braces);
    return flag;
}
