#include <cs50.h>
#include <stdio.h>

int     main(void)
{
    int n;
    do
    {
        n = get_int("Number: ");
    }
    while (!(n > 0 && n < 9));
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            if (j < i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        for (int k = 0; k < n - i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
