#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int E(char ip);
int Tdash(char ip);
int Edash(char ip);
int F(char ip);
int T(char ip);
void advance(char string[], char ip);

char string[5];
int k = 0;

int E(char ip)
{
    if (T(ip))
    {
        if (Edash(ip))
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

int T(char ip)
{
    if (F(ip))
    {
        if (Tdash(ip))
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

int Tdash(char ip)
{
    if (ip == '*')
    {
        advance(string, ip);
        if (F(ip))
        {
            if (Tdash(ip))
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    return 1;
}

int Edash(char ip)
{
    if (ip == '+')
    {
        advance(string, ip);
        if (T(ip))
        {
            if (Edash(ip))
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    return 1;
}

int F(char ip)
{
    if (ip == '(')
    {
        advance(string, ip);
        if (E(ip))
        {
            if (ip == ')')
            {
                advance(string, ip);
                return 1;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else if (islower(ip))
    {
        advance(string, ip);
        return 1;
    }
    else
        return 0;
}

void advance(char string[], char ip)
{
    ip = string[++k];
}

void main()
{

    printf("Enter the string to be parsed : ");
    scanf("%s", string);

    printf("\nEntered string : %s", string);

    int val = E(string[0]);
    if (val == 0)
    {
        printf("\nThe string doesnt belong to the grammar!\n");
    }
    else
        printf("\nThe string belongs to the grammar!\n");
}
