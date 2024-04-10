#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{

    // TODO
    int num = 0;
    int sign = 1;
    int len = strlen(input);
    if (len < 1)
        return 0;
    int now = (input[len - 1] - '0');
    input[len - 1] = '\0';
    num = 10 * convert(input) + now;

    return num;
}
