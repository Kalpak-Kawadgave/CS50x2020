//libraries
#include<cs50.h>
#include<stdio.h>
#include<math.h>

int main(void)
{
    // prompt user for positive number
    float i;
    do
    {
        i = get_float("Change owed: ");
    }
    while (i < 0);

    // calculation of optimal solution
    int j = round(100 * i);
    int a = j / 25;
    int b = (j % 25) / 10;
    int c = ((j % 25) % 10) / 5;
    int d = (((j % 25) % 10) % 5) / 1;
    int e = a + b + c + d;

    //print the solution
    printf("%i\n", e);
}
