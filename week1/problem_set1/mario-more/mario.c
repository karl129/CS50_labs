#include <cs50.h>
#include <stdio.h>

int get_size();
void plot_blocks(int n);

int main(void)
{
    int n = get_size();
    plot_blocks(n);
}

int get_size()
{
    int n;
    do
    {
        n = get_int("Heigh: ");
    }
    while (n > 8 || n <= 0);

    return n;
}

void plot_blocks(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j < n - i - 1)
                printf(" ");
            else
                printf("#");
        }
        printf("  ");
        for (int j = 0; j < i+1; j++)
            printf("#");
        printf("\n");
    }
}
