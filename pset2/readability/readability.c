#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int     main(void)
{
    string str = get_string("Text: ");

    int i = 0;
    int l = 0, w = 0, s = 0;
    while (i < strlen(str))
    {
        if (isalpha(str[i]))
        {
            l++;
        }
        else if (str[i] == ' ' && str[i - 1] != '.' && str[i - 1] != '!' && str[i - 1] != '?')
        {
            w++;
        }
        else if (str[i] == '.' || str[i] == '!' || str[i] == '?')
        {
            s++;
            w++;
        }
        i++;
    }
    float let = ((float)l / w) * 100;
    float sen = ((float)s / w) * 100;
    float in = 0.0588 * let - 0.296 * sen - 15.8;
    int index = round(in);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index < 16)
    {
        printf("Grade %d\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

