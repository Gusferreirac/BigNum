#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseString(char *str1)
{
    int i, len, temp;
    len = strlen(str1);

    for (i = 0; i < len / 2; i++)
    {
        temp = str1[i];
        str1[i] = str1[len - i - 1];
        str1[len - i - 1] = temp;
    }
}