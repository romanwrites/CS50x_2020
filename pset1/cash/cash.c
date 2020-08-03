#include <cs50.h>
#include <math.h>
#include <stdio.h>

int         main(void)
{
    int   quarters = 25;
    int   dimes = 10;
    int   nickels = 5;
    int   pennies = 1;
    int     coins = 0;
    int     cents;
    float dollars;

    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);
    cents = round(dollars * 100);
    if ((cents % quarters) < cents)
    {
        coins += cents / quarters;
        cents -= quarters * (cents / quarters);
    }
    if ((cents % dimes) < cents)
    {
        coins += cents / dimes;
        cents -= dimes * (cents / dimes);
    }
    if ((cents % nickels) < cents)
    {
        coins += cents / nickels;
        cents -= nickels * (cents / nickels);
    }
    if ((cents % pennies) < cents)
    {
        coins += cents / pennies;
        cents -= pennies * (cents / pennies);
    }
    printf("%d\n", coins);
}
