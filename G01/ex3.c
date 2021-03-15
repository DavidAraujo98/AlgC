#include <stdio.h>
#include <math.h>

int main(void)
{
    int in;

    printf("How many lines should the table have: ");

    scanf("%d", &in);

    printf("n\tn^2\tsqrt\n");

    for (int i = 1; i <= in; i++)
    {
        int a = i * i;
        double b = sqrt(i);

        printf("%d\t%d\t%lf\n", i, a, b);
    }
}