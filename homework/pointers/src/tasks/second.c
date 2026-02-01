#include <stdio.h>

void second_task(void)
{
    float x = 5.0;
    printf("x = %f, ", x);

    float y = 6.0;
    printf("y = %f\n", y);

    float* xp = &y; // было float* xp = &x; 
    float* yp = &y;

    printf("Результат: %f\n", *xp + *yp);
}
