#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int KEY_LEN = 26;

string cipher(string plaintext, string key);
bool is_argvalid(string arg);
bool is_goodkey(string key, int len);

int main(int argc, string argv[])
{
    if (argc == 2 && is_argvalid(argv[1]))
    {
        string key = argv[1];
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

// 检查key是否合格
bool is_argvalid(string arg)
{
    int len = strlen(arg);
    if (len == KEY_LEN && is_goodkey(arg, KEY_LEN))
        return true;
    else
        return false;
}

// 辅助is_argvalid函数，检查有无非字母和重复
bool is_goodkey(string key, int len)
{
    char flags[len];
    for (int i = 0; i < len; i++)
    {
        flags[i] = 'a';
    }
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(key[i]))
            return false;
        else
        {
            if (isalpha(flags[toupper(key[i]) - 65]))
                flags[toupper(key[i]) - 65] = '*';
            else
                return false;
        }
    }
    return true;
}

// 加密函数
string cipher(string plaintext, string key)
{
    int len = strlen(plaintext);
    char *ciphertext = (char *) malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i++)
    {
        if (islower(plaintext[i]))
            ciphertext[i] = tolower(key[plaintext[i] - 97]);
        else if (isupper(plaintext[i]))
            ciphertext[i] = toupper(key[plaintext[i] - 65]);
        else
            ciphertext[i] = plaintext[i];
    }
    ciphertext[len] = '\0';
    return ciphertext;
}
