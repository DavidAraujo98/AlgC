#include <stdio.h>
#include <math.h>

int main(void)
{
    double start, end, spc;

    printf("Starting angle: ");
    scanf("%lf", &start);

    printf("Maximum angle: ");
    scanf("%lf", &end);

    printf("Space between angles: ");
    scanf("%lf", &spc);

    printf("n\tsen\tcos\n");

    for (double i = start; i <= end; i += spc)
    {
        double a = sin(i * (M_PI / 180));
        double b = cos(i * (M_PI / 180));

        printf("%.2lf\t%.2lf\t%.2lf\n", i, a, b);
    }
}