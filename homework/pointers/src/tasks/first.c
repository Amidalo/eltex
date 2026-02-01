#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "../../include/first.h"

#define NULL_TERMINATOR 1
#define BITS_IN_BYTE 8
#define BITS_IN_INT32_T sizeof(int32_t) * 8

void change_value_of_3bytes_with_pointer(void)
{
    uint8_t binary[BITS_IN_INT32_T + NULL_TERMINATOR] = { 0 };
    uint8_t binary_byte[BITS_IN_BYTE + NULL_TERMINATOR] = { 0 };

    uint32_t input_number = 0;
    uint32_t modified_input_number = 0;
    // short (uint16_t) для проверки вводимого диапазона и дальнейшего преобразования в char (uint8_t)
    uint16_t input_byte = 0;

    printf("Введите положительное число, где будем менять значение 3 байта: ");
    scanf("%u", &input_number);

    modified_input_number = input_number;

    binary[BITS_IN_INT32_T] = '\0';
    uint8_t* ptr = binary + (BITS_IN_INT32_T - 1); // Указатель на предпоследний элемент, потому что последний - \0 [32]
    int number_of_processed_bits = 0;

    uint32_t temp_input_number = input_number;

    while (number_of_processed_bits < BITS_IN_INT32_T)
    {
        *ptr = (temp_input_number % 2) + '0';
        temp_input_number /= 2;
        ptr--;
        number_of_processed_bits++;
    }
    printf("Двоичное представление целого положительного числа: %s\n", binary);

    printf("Введите значение байта (0 - 255): ");
    scanf(" %hu", &input_byte);

    if (input_byte < 0 || input_byte > UINT8_MAX)
    {
        printf("Ошибка: байт должен быть в диапазоне 0 - 255!\n");
        return;
    }

    uint8_t true_byte = (uint8_t) input_byte;

    binary_byte[BITS_IN_BYTE] = '\0';
    uint8_t* ptr_b = binary_byte + (BITS_IN_BYTE - 1);
    number_of_processed_bits = 0;

    uint8_t temp_true_byte = true_byte;

    while (number_of_processed_bits < BITS_IN_BYTE)
    {
        *ptr_b = (temp_true_byte % 2) + '0';
        temp_true_byte /= 2;
        ptr_b--;
        number_of_processed_bits++;
    }
    printf("Двоичное представление значения байта: %s\n", binary_byte);

    uint8_t* ptr_3byte = (uint8_t*)&modified_input_number; // Сейчас указывает на нулевой байт
    *(ptr_3byte + 3) = true_byte;

    ptr = binary + (BITS_IN_INT32_T - 1);
    number_of_processed_bits = 0;

    temp_input_number = modified_input_number;

    while (number_of_processed_bits < BITS_IN_INT32_T)
    {
        *ptr = (temp_input_number % 2) + '0';
        temp_input_number /= 2;
        ptr--;
        number_of_processed_bits++;
    }

    printf("Двоичное представление целого положительного числа после замены 3 байта: %s\n", binary);
    printf("Десятичное представление после замены: %u\n", modified_input_number);

}