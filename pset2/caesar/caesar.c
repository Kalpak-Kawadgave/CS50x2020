//libraries
#include<cs50.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

string encipher();

//main function that accepts one command line arguments
int main(int argc, string argv[])
{

    // check if the argument count is 2
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //get the sting lenth of argv[1]
    int length = strlen(argv[1]);

    // check if the first command line argument is an interger
    for (int c = 0; c < length; c++)
    {
        if (argv[1][c] >= 48 && argv[1][c] <= 57)
        {
            int f = 0;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //convert the argv[1] to integer for the value of key
    int key = 0;
    key = atoi(argv[1]);
    key = key % 26;

    string input = get_string("plaintext:  ");

    //print output
    printf("ciphertext: %s\n", encipher(key, input));
    return 0;
}

string encipher(int a, string b)
{
    for (int c = 0; c < strlen(b); c++)
    {
        //for capital letters
        if (b[c] >= 65 && b[c] <= 90)
        {
            b[c] = b[c] + a;
            if (b[c] > 90)
            {
                b[c] = b[c] - 26;
            }
        }

        //for small letters
        if (b[c] >= 97 && b[c] <= 122)
        {
            b[c] = b[c] + a - 26;
            if (b[c] < 97)
            {
                b[c] = b[c] + 26;
            }
        }

        //for non alphabetic characters
        else
        {
            b[c] = b[c];
        }
    }
    return b;
}