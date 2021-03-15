#include <stdio.h>

int main(void)
{

    char name[50];

    printf("Your name: ");

    scanf("%[^\n]s", name);

    printf("Hello %s !\n", name);

    return 0;
}