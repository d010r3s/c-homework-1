#include <stdio.h>
#include <math.h>
#include "tinyexpr.h"


typedef double (*TFunc)(te_expr*, double*, double);
double diff(TFunc f, te_expr *expr, double *_x, double x, double dx);
double f(te_expr *expr, double *x, double new_x);

int main() {
    int err, n;
    double x;
    char c[30];
    te_variable vars[] = {{"x", &x}};

    printf("Function: ");
    scanf("%s", &c);
    printf("Approximation: ");
    scanf("%lf", &x);
    printf("Iterations: ");
    scanf("%d", &n);

    te_expr *expr = te_compile(c, vars, 1, &err);

    for (int i = 0; i < n; ++i) {
        x = x - te_eval(expr) / diff(f, expr, &x, x, 1e-10);
    }
    printf("Answer: %f \n", x);
}

double diff(TFunc f, te_expr *expr, double *_x, double x, double dx) {
    double dy = f(expr, _x, x+dx)  - f(expr, _x, x-dx);
    return dy/(2.*dx);
}

double f(te_expr *expr, double *x, double new_x) { 
    *x = new_x;
    return te_eval(expr);
}