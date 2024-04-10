// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

void leetspeak(string word);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        leetspeak(argv[1]);
        return 0;
    }
    else
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
}

void leetspeak(string word)
{
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        switch (word[i])
        {
            case 'a':
                printf("6");
                break;
            case 'e':
                printf("3");
                break;
            case 'i':
                printf("1");
                break;
            case 'o':
                printf("0");
                break;
            default:
                printf("%c", word[i]);
                break;
        }
    }
     printf("\n");
}
