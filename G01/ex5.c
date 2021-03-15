#include <stdio.h>

int main(void)
{
    char a;
    short int b;
    long int c;
    int d;
    float e;
    double f;
    long double g;
    int *h;
    char *i;
    float *j;

    printf("Size of char: %ld bytes\n", sizeof(a));
    printf("Size of short int: %ld bytes\n", sizeof(b));
    printf("Size of long int: %ld bytes\n", sizeof(c));
    printf("Size of int: %ld bytes\n", sizeof(d));
    printf("Size of float: %ld bytes\n", sizeof(e));
    printf("Size of double: %ld bytes\n", sizeof(f));
    printf("Size of long double: %ld bytes\n", sizeof(g));
    printf("Size of int pointer: %ld bytes\n", sizeof(h));
    printf("Size of char pointer: %ld bytes\n", sizeof(i));
    printf("Size of float pointer: %ld bytes\n", sizeof(j));
}