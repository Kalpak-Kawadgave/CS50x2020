//libraries
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

string encipher();

//initializing main program
int main(int argc, string argv[])
{
    //check for arg count of two
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //check for length of argv[1]
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //chech if key is alphabetic
    for (int c = 0; c < 26; c++)
    {
        if (isalpha(argv[1][c]) == 0)
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
    }

    for (int c = 0; c < 26; c++)
    {
        if (argv[1][c] >= 65 && argv[1][c] <= 90)
        {
            argv[1][c] = argv[1][c] + 32;
        }
    }

    //check for a valid key
    for (int c = 0; c < 26; c++)
    {
        for (int d = c + 1; d < 26; d++)
        {
            if (argv[1][c] == argv[1][d])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    string input = get_string("plaintext:  ");
    printf("ciphertext: %s\n", encipher(argv[1], input));
    return 0;
}

string encipher(string a, string b)
{
    for (int c = 0; c < strlen(b); c++)
    {
        //for capital letters
        if (b[c] >= 65 && b[c] <= 90)
        {
            b[c] = toupper(a[b[c] - 65]);
        }

        //for small letters
        if (b[c] >= 97 && b[c] <= 122)
        {
            b[c] = (a[b[c] - 97]);
        }

        //for non alphabetic characters
        else
        {
            b[c] = b[c];
        }
    }
    return b;
}