#include <stdio.h>
#include <limits.h>

int main(void)
{
    char binary[sizeof(short) * 8 + 1] = {0};
    char shift = sizeof(short) * 8 - 1;
    short count_of_one = 0;

    signed int input = 0;
    unsigned short number = 0;

    printf("Введите число (0 <= число <= 65535): ");
    scanf("%d", &input);

    if (input > USHRT_MAX)
    {
        printf("\nВы вышли из диапазона типа unsigned short (0-65535)!"
               "\nВаше число %d будет преобразовано в %d из-за циклического переполнения!\n", input, input - USHRT_MAX - 1);
    }

    if (input < 0)
    {
        printf("\nВы вышли из диапазона типа short (0-65535)!"
               "\nВаше число %d будет преобразовано в %d из-за циклического переполнения!\n\ns", input, input + USHRT_MAX + 1);
    }

    number = (unsigned short)input;
    short bit = 0;

    short i = 0;
    for (; i <= sizeof(short) * 8 - 1; i++)
    {
        bit = (number >> shift) & 1;
        if (bit == 1) count_of_one++;

        *(binary + i) = bit + '0';
        shift--;
    }
    *(binary + i) = '\0';

    printf("Двоичное представление: %s", binary);
    printf("\nКоличество единиц: %d\n", count_of_one);

    return 0;
}
