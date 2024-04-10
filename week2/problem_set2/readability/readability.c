#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *counter(string text);
int readability_checker(int array[]);
void print_grade(int grade);
int main(void)
{
    string text = get_string("Text: ");

    int *counters = counter(text);

    int grade = readability_checker(counters);
    print_grade(grade);
}

int *counter(string text)
{
    int *counters = (int *) malloc(3 * sizeof(int));
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
            counters[0]++;
        else if (text[i] == ' ')
            counters[1]++;
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
            counters[2]++;
    }
    counters[1]++;

    return counters;
}

int readability_checker(int counters[])
{
    float l = (float) counters[0] / counters[1] * 100.0;
    float s = (float) counters[2] / counters[1] * 100.0;

    float index = 0.0588 * l - 0.296 * s - 15.8;

    return (int) (index + 0.5);
}

void print_grade(int grade)
{
    if (grade < 1)
        printf("Before Grade 1\n");
    else if (grade >= 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", grade);
}
