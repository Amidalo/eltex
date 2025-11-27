#include <stdio.h>

int main(void)
{
    signed short number = 0;
    char binary[sizeof(short) * 8 + 1];
    char shift = sizeof(short) * 8 - 1;

    printf("Введите число (-32768 <= число < 0): ");
    scanf("%hd", &number);

    if (number >= 0)
    {
        printf("Вы вышли из допустимого диапазона!\n");
        return 1;
    }

    short i = 0;
    for (; i <= sizeof(short) * 8 - 1; i++)
    {
        binary[i] = ((number >> shift) & 1) + '0';
        shift--;
    }
    binary[i] = '\0';

    puts(binary);
    

    return 0;
}
