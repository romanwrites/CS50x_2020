#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

_Bool   all_isalpha(char *s)
{
    for (int i = 0; s[i]; i++)
    {
        if (!isalpha(s[i]))
        {
            return (0);
        }
    }
    return (1);
}

_Bool   has_dups(char *s)
{
    for (int i = 0; s[i]; i++)
    {
        for (int j = i + 1; s[j]; j++)
        {
            if (s[i] == s[j])
            {
                return (1);
            }
        }
    }
    return (0);
}

int     main(int ac, char **av)
{
    if (ac != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    if (strlen(av[1]) != 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }
    else if (!all_isalpha(av[1]))
    {
        return 1;
    }
    else if (has_dups(av[1]))
    {
        return 1;
    }
    char *key = av[1];
    for (int i = 0; key[i]; i++)
    {
        key[i] = toupper(key[i]);
    }
    string plaintext = get_string("plaintext: ");
    string tab = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; plaintext[i]; i++)
    {
        for (int j = 0; tab[j]; j++)
        {
            if (toupper(plaintext[i]) == tab[j])
            {
                if (isupper(plaintext[i]))
                {
                    plaintext[i] = key[j];
                }
                else
                {
                    plaintext[i] = tolower(key[j]);
                }
                break ;
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
    return (0);
}

