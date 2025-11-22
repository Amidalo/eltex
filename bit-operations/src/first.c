#include <stdio.h>
#include <limits.h>

int main(void)
{
    short number = 0;
    char binary[sizeof(short) * 8 + 1] = {0};
    char shift = sizeof(short) * 8 - 1;

    printf("Enter a positive SHORT number: ");
    scanf("%hd", &number);

    if (number < 0 || number > 32767 || number % 2 != 0)
    {
        printf("You can enter a WHOLE number in this range: 0 <= number <= 32767\n");
        return 1;
    }

    short i = 0;
    for (; i <= sizeof(short) * 8 - 1; i++)
    {
        binary[i] = ((number >> shift) & 1) + '0';
        shift--;
    }
    binary[i] = '\0';

    printf("%s\n", binary);

    return 0;
}
