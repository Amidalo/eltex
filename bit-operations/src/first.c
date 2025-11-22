#include <stdio.h>

int main(void)
{
    unsigned short number = 0;
    char binary[sizeof(short) * 8 + 1] = {0};
    char shift = sizeof(short) * 8 - 1;

    printf("Enter a positive SHORT number: ");
    scanf("%hu", &number);

    short i = 0;
    for (; i <= sizeof(short) * 8 - 1; i++)
    {
        binary[i] = ((number >> shift) & 1) + '0';
        shift--;
    }
    binary[i] = '\0';

    printf("%s\n", binary);
    
    
}
