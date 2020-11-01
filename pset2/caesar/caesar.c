#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

/* checks if all chars are digits or not */
bool    is_all_digits(string s)
{
    for (int i = 0; s[i]; i++)
    {
        if (!isdigit(s[i]))
        {
            return (0);
        }
    }
    return (1);
}

int     main(int ac, char **av)
{
    if (ac == 2)
    {
        if (!is_all_digits(av[1]))
        {
            return (1);
        }
        int key = atoi(av[1]) % 26;
        string s = get_string("plaintext: ");
        for (int i = 0; s[i]; i++)
        {
            if (isalpha(s[i]))
            {
                /* handle border cases */
                if ((isupper(s[i]) && ((unsigned char)s[i] + key) > 90) || \
                    (islower(s[i]) && ((unsigned char)s[i] + key) > 122))
                {
                    s[i] = (char)((unsigned char)s[i] + key - 26);
                }
                else
                {
                    s[i] = (char)((unsigned char)s[i] + key);
                }
            }
        }
        printf("ciphertext: %s\n", s);
        return (0);
    }
    /* if args count is not right */
    return (1);
}
