// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);
bool issymbol(char c);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

bool valid(string password)
{
    bool uflag = false, lflag = false, nflag = false, sflag = false;
    int len = strlen(password);
    for (int i = 0; i < len; i++)
    {
        if (isupper(password[i]))
            uflag = true;
        else if (islower(password[i]))
            lflag = true;
        else if (isalnum(password[i]))
            nflag = true;
        else if (issymbol(password[i]))
            sflag = true;
    }
    if (uflag && lflag && nflag && sflag)
        return true;
    else
        return false;
}

// 判断是否是符号
bool issymbol(char c)
{
    if (c == '#' || c == '!' || c == '$')
        return true;
    else
        return false;
}
