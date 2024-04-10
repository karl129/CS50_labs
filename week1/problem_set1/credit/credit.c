#include <cs50.h>
#include <stdio.h>

int get_last(long num);
int get_first2(long num);
int get_check(long card);
int get_len(long num);
bool checksum_valid(int checksum);

int main(void)
{
    long card_id = get_long("Number: ");

    int first2 = get_first2(card_id);
    // VISA
    if ((first2 >= 40 && first2 <= 49))
    {
        int len = get_len(card_id);

        if (len == 13 || len == 16)
        {
            int checksum = get_check(card_id);
            if (checksum_valid(checksum))
                printf("VISA\n");
            else
                printf("INVALID\n");
        }
        else
            printf("INVALID\n");
    }
    // AMEX
    else if (first2 == 34 || first2 == 37)
    {
        int len = get_len(card_id);
        if (len == 15)
        {
            int checksum = get_check(card_id);
            if (checksum_valid(checksum))
                printf("AMEX\n");
            else
                printf("INVALID\n");
        }
        else
            printf("INVALID\n");
    }
    // MASTERCARD
    else if (first2 >= 51 && first2 <= 55)
    {
        int len = get_len(card_id);
        if (len == 16)
        {
            int checksum = get_check(card_id);
            if (checksum_valid(checksum))
                printf("MASTERCARD\n");
            else
                printf("INVALID\n");
        }
        else
            printf("INVALID\n");
    }
    else
        printf("INVALID\n");
    return 0;
}

// 获取最后一位
int get_last(long num)
{
    if (num < 10)
        return num;
    else
    {
        get_last(num / 10);
        return (num % 10);
    }
}

// 获取2位
int get_first2(long num)
{
    while (num >= 100)
        num /= 10;
    return num;
}

// 获取长度
int get_len(long num)
{
    int len = 0;
    while (num > 0)
    {
        len++;
        num /= 10;
    }
    return len;
}

// 得到校验码
int get_check(long card)
{
    int checksum;
    int s_sum = 0, d_sum = 0;

    for (int i = 0; card > 0; card /= 10, i++)
    {
        if (i % 2 != 0)
        {
            int d_last = get_last(card) * 2;
            if (d_last > 9)
                d_sum = d_sum + get_last(d_last) + get_last(d_last / 10);
            else
                d_sum += d_last;
        }
        else
        {
            s_sum += get_last(card);
        }
    }
    checksum = s_sum + d_sum;

    return checksum;
}

// 检查校验码
bool checksum_valid(int checksum)
{
    if (checksum % 10 == 0)
        return true;
    else
        return false;
}
