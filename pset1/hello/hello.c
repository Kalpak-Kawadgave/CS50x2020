//Libraries
#include <cs50.h>
#include <stdio.h>

//initiate the main program
int main(void)
{
    //prompt the user for name
    string name = get_string("What is your name?\n");

    // print hello with the users name
    printf("hello, %s\n", name);
}