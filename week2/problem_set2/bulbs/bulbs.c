#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
int *get_binary(char letter);
void print_line(int *bin);

int main(void)
{
    string message = get_string("Message: ");
    int len = strlen(message);
    for (int i = 0; i < len; i++)
    {
        int *binary = get_binary(message[i]);
        print_line(binary);
    }
    free(binary);
    return 0;
}

// 得到单个字符的二进制表示，返回一个数组
int *get_binary(char letter)
{
    int *bin = (int *) malloc(sizeof(int) * 8);
    if (bin == NULL)
    {
        return 1;
    }
    for (int i = BITS_IN_BYTE - 1; i >= 0; i--)
    {
        bin[i] = letter % 2;
        letter /= 2;
    }
    return bin;
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

// 绘制一行（单个字符）
void print_line(int *bin)
{
    for (int i = 0; i < BITS_IN_BYTE; i++)
        print_bulb(bin[i]);
    printf("\n");
}
