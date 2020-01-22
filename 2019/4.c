#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 6
#define arrayLength(arr) (sizeof(arr)/sizeof((arr)[0]))

int validPart1(int digits[], int min, int max)
{
    int valid = 0;

    for (int i = 0; i < MAX_DIGITS - 1; i++)
    {
        if (digits[i] == digits[i + 1])
        {
            valid = 1;
            break;
        }
    }

    if (valid)
    {
        int x = digits[0] * 100000 +
                digits[1] * 10000 +
                digits[2] * 1000 +
                digits[3] * 100 +
                digits[4] * 10 +
                digits[5];

        valid = x >= min && x <= max;

        if (valid)
            printf("%d\n", x);
    }

    return valid;
}

int validPart2(int digits[], int min, int max)
{
    int valid = 0;

    for (int i = 0; i < MAX_DIGITS - 1; i++)
    {
        if (digits[i] == digits[i + 1])
        {
            if ((i == 0 || digits[i - 1] != digits[i]) &&
                (i == MAX_DIGITS - 2 || digits[i + 2] != digits[i + 1]))
            {
                valid = 1;
                break;
            }
        }
    }

    if (valid)
    {
        int x = digits[0] * 100000 +
                digits[1] * 10000 +
                digits[2] * 1000 +
                digits[3] * 100 +
                digits[4] * 10 +
                digits[5];

        valid = x >= min && x <= max;
    }

    return valid;
}

int comb2(int min, int max, int digits[], int index, int startDigit)
{
    if (index >= MAX_DIGITS)
    {
        // if (validPart1(digits, min, max))
        // {
        //     return 1;
        // }

        if (validPart2(digits, min, max))
        {
            return 1;
        }

        return 0;
    }

    int n = 0;

    for (int s = startDigit; s < 10; s++)
    {
        digits[index] = s;
        n += comb2(min, max, digits, index + 1, s);
    }

    return n;
}

int comb1(int min, int max)
{
    int digits[MAX_DIGITS];
    memset(digits, 0, sizeof(digits));
    int n = comb2(min, max, digits, 0, 1);
    return n;
}

int main()
{
    printf("%d\n", comb1(178416, 676461));
    return 0;
}