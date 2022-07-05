//libraries
#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

//defining the functioons to be used
int letters();
int words();
int sentences();

//main function
int main(void)
{
    //prompt user for input
    string grade = get_string("Text: ");

    //storing value of string length
    int length = strlen(grade);

    //calling letters function
    int l = letters(length, grade);

    //calling words function
    int w = words(length, grade);

    //calling sentences function
    int s = sentences(length, grade);

    //calculator for the grade of text
    float L = (float) l / w * 100;
    float S = (float) s / w * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int x = round(index);


    //printing the grade of the text
    if (x >= 1 && x <= 16)
    {
        printf("Grade %i\n", x);
    }
    else if (x < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }

}

//defining function for counting letters
int letters(int a, string b)
{
    int c = 0;
    for (int q = 0; q < a; q++)
    {

        if ((b[q] >= 'a' && b[q] <= 'z') || (b[q] >= 'A' && b[q] <= 'Z'))
        {
            c++;
        }
    }
    return c;
}

//defining function for counting words
int words(int a, string b)
{
    int c = 1;
    for (int q = 0; q < a; q++)
    {

        if (b[q] == ' ')
        {
            c++;
        }
    }
    return c;
}

//defining function for counting sentences
int sentences(int a, string b)
{
    int c = 0;
    for (int q = 0; q < a; q++)
    {

        if (b[q] == '.' || b[q] == '?' || b[q] == '!')
        {
            c++;
        }
    }
    return c;
}