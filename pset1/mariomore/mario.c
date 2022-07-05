//libraries
#include<cs50.h>
#include<stdio.h>

int get_input();


//main function
int main(void)
{
    int i = get_input();

    for (int j = i - 1; j >= 0; j--)
    {

        // print spaces
        for (int a = 0; a < j; a++)
        {
            printf(" ");
        }

        //print #
        for (int k = i; k > j; k--)
        {
            printf("#");
        }

        printf("  ");

        //print #
        for (int k = i; k > j; k--)
        {
            printf("#");
        }
        printf("\n");
    }
}


//prompt user for input
int get_input()
{
    int a;

    do
    {
        a = get_int("Height: ");
    }
    while (a >= 9 || a <= 0);

    return a;
}