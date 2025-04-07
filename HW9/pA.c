#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double power(double x, int n){
    return pow(x, n);
}

double multiply(double x, int n){
    return x*n;
}

double divide(double x, int n){
    return x/n;
}



// 輸入的function是()內要做的事，而不是power
double powerpower(double (*function)(double, int), double x, int n, int m){
    double temp = function(x, n);
    double result = power(temp, m);
    return result;
}

double powermultiply(double (*function)(double, int), double x, int n, int m){
    double temp = function(x, n);
    double result = multiply(temp, m);
    return result;
}

double powerdivide(double (*function)(double, int), double x, int n, int m){
    double temp = function(x, n);
    double result = divide(temp, m);
    return result;
}

// ./pA x n m
int main(int agrc, char *argv[]){
    double x = atof(argv[1]);
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);

    printf("%f\n", powerpower(power, x, n, m));
    printf("%f\n", powerpower(multiply, x, n, m));
    printf("%f\n", powerpower(divide, x, n, m));
    printf("%f\n", powermultiply(power, x, n, m));
    printf("%f\n", powermultiply(multiply, x, n, m));
    printf("%f\n", powermultiply(divide, x, n, m));
    printf("%f\n", powerdivide(power, x, n, m));
    printf("%f\n", powerdivide(multiply, x, n, m));
    printf("%f\n", powerdivide(divide, x, n, m));
}