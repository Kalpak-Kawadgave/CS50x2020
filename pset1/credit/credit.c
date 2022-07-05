//libraries
#include<cs50.h>
#include<stdio.h>

int main(void)

{
    // Prompt for input
    long n = get_long("Number: ");
    //counter to determine the length of long
    long m = n;
    int c = 0;
    long q = n;
    do
    {
        c++;
        m = m / 10;
    }
    while (m > 0);
    //check for valid length of number
    if (c > 12 && c < 17)
    {
        // Definining the variables required
        int z = 0;
        int sum = 0;
        int a = 0;
        int b = 0;
        int g;
        int h;
        //calcalator for Luhn's algorithm
        do
        {
            // adder for the reamining digits
            if (z % 2 == 0)
            {
                a = n % 10;
                n = n / 10;
                sum = sum + a;
            }
            //adder for last second and every other digit *2
            else
            {
                b = n % 10;
                n = n / 10;
                g = 2 * b;
                //defined h to to add digits of 2 digit numbers
                h = g % 10 + g / 10;
                sum = sum + h;
            }
            z++;
        }
        while (z < c + 2);
        //Luhn's check for last digit
        if (sum % 10 == 0)
        {
            //Determine the type of card
            for (int o = 0; o < c - 2; o++)
            {
                q = q / 10;
            }
            if (q == 34 || q == 37)
            {
                printf("AMEX\n");
            }
            else if (q > 50 && q < 56)
            {
                printf("MASTERCARD\n");
            }
            else if (q / 10 == 4)
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