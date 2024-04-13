#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidX(const char *str, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        if (str[i] == 'b' && (str[i + 1] == 'b' || str[i + 1] == 'c'))
        {
            i++;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool validateString(const char *str)
{
    int len = strlen(str);

    if (len < 2) return false;
    if (str[0] != 'a' || str[len - 1] != 'd') return false;

    if (len == 2) return true;
    return isValidX(str, 1, len - 1);
}

int main()
{
    char input[1024];

    printf("Enter a string to validate: ");
    scanf("%s", input);

    if (validateString(input))
    {
        printf("The string is valid according to the given CFG.\n");
    }
    else
    {
        printf("The string is invalid according to the given CFG.\n");
    }

    return 0;
}

