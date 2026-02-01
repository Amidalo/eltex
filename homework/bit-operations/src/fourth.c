#include <stdio.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
    char binary[sizeof(int) * 8 + 1] = {0};
    char shift = sizeof(int) * 8 - 1;

    unsigned int number = 0;
    int byte_input = 0;

    printf("Введите положительное число, где будем менять 3 байт: ");
    scanf("%u", &number);

    printf("Введите значение unsigned байта (0 - 255): ");
    scanf(" %d", &byte_input);

    if (byte_input < 0 || byte_input > 255) {
        printf("Ошибка: байт должен быть в диапазоне 0 - 255!\n");
        return 1;
    }

    unsigned char true_byte = (unsigned char)byte_input;

    int result = (number & 0x00FFFFFF) | ((true_byte & 0xFF) << 24);

    short i = 0;
    for (; i <= sizeof(int) * 8 - 1; i++)
    {
        *(binary + i) = ((result >> shift) & 1) + '0';
        shift--;
    }
    *(binary + i) = '\0';
    
    printf("\nДвоичное представление: %s\n", binary);

    return 0;
}
