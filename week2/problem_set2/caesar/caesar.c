#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string cipher(string plaintext, int key);
bool is_argvalid(string arg);
int get_key(string arg);

int main(int argc, string argv[])
{
    if (argc == 2 && is_argvalid(argv[1]))
    {
        int key = get_key(argv[1]);
        string plaintext = get_string("plaintext: ");

        string ciphertext = cipher(plaintext, key);

        printf("ciphertext: %s\n", ciphertext);

        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

string cipher(string plaintext, int key)
{
    int len = strlen(plaintext);
    char *ciphertext = (char *) malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i++)
    {
        if (islower(plaintext[i]))
            ciphertext[i] = (plaintext[i] - 97 + key) % 26 + 97;
        else if (isupper(plaintext[i]))
            ciphertext[i] = (plaintext[i] - 65 + key) % 26 + 65;
        else
            ciphertext[i] = plaintext[i];
    }
    ciphertext[len] = '\0';
    return ciphertext;
}

// 检验参数是否有效
bool is_argvalid(string arg)
{
    int len = strlen(arg);
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(arg[i]))
            return false;
    }
    return true;
}

// 计算出相应的 key
int get_key(string arg)
{
    int key = 0;
    int times = 1;
    int len = strlen(arg);
    for (int i = len - 1; i >= 0; i--)
    {
        key += (arg[i] - 48) * times;
        times *= 10;
    }
    return key;
}
