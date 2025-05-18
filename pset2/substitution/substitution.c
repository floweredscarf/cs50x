#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char substitute(char letter, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    string key = argv[1];
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        key[i] = toupper(key[i]);
    }
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (key[j] == key[i] && i != j)
            {
                return 1;
            }
        }
    }
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c", substitute(plaintext[i], key));
    }
    printf("\n");
    return 0;
}

char substitute(char letter, string key)
{
    if (isupper(letter))
    {
        letter = key[letter - 'A'];
        return letter;
    }
    else if (islower(letter))
    {
        letter = tolower(key[letter - 'a']);
        return letter;
    }
    else
    {
        return letter;
    }
}