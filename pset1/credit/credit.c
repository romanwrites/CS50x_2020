#include <cs50.h>
#include <math.h>
#include <stdio.h>

int     main(void)
{
    long    card;
    int     ones = 0;
    int     twos = 0;
    int     click = 0;
    int     id = 0;
    int     digits = 0;
    long    card_copy;
    int     pre_twos;

    do
    {
        card = get_long("Number: ");
    }
    while (card < 0);
    card_copy = card;
    while (card_copy > 0)
    {
        card_copy = card_copy / 10;
        digits++;
    }
    if (digits == 13 || digits == 15 || digits == 16)
    {
        while (card > 0)
        {
            if (card < 100 && !id)
            {
                id = card;
            }
            if (click == 0)
            {
                ones += card % 10;
                card = card / 10;
                click = 1;
            }
            else if (click == 1)
            {
                pre_twos = (card % 10) * 2;
                if (pre_twos > 9)
                {
                    pre_twos = pre_twos % 10 + (pre_twos / 10);
                }
                twos += pre_twos;
                card = card / 10;
                click = 0;
            }
        }
        if ((twos + ones) % 10 == 0)
        {
            if ((id == 34 || id == 37) && digits == 15)
            {
                printf("AMEX\n");
            }
            else if ((id >= 51 && id <= 55) && digits == 16)
            {
                printf("MASTERCARD\n");
            }
            else if ((id >= 40 && id <= 49) && (digits == 13 || digits == 16))
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

