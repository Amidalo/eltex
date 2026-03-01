#include "utils.h"
#include "calc_operations.h"

int main(void)
{
    char the_fifth_case_is_not_selected = 1;
    char user_input = 0;
    int first_number = 0;
    int second_number = 0;
    double result = 0;

    printf("\n Добро пожаловать в калькулятор! \n");

    printf("\n Внимание: вы можете вводить только целые числа. Дробная часть будет отрезаться! \n");

    while (the_fifth_case_is_not_selected)
    {
        print_text_menu();

        scanf(" %c", &user_input);
        clean_stdin(); // Очистка входного буфера stdin из-за '\n'

        switch (user_input)
        {
            case '1':
            {
                printf("\n Введите первое слагаемое: ");
                first_number = enter_a_number();

                printf("\n Введите второе слагаемое: ");
                second_number = enter_a_number();

                result = add(first_number, second_number);
                printf("\n Результат %d + %d равен %.0f \n", first_number, second_number, result);

                break;
            }
            case '2':
            {
                printf("\n Введите уменьшаемое: ");
                first_number = enter_a_number();

                printf("\n Введите вычитаемое: ");
                second_number = enter_a_number();

                result = sub(first_number, second_number);
                printf("\n Результат %d - %d равен %.0f \n", first_number, second_number, result);

                break;
            }
            case '3':
            {
                printf("\n Введите первый множитель: ");
                first_number = enter_a_number();

                printf("\n Введите второй множитель: ");
                second_number = enter_a_number();

                result = mul(first_number, second_number);
                printf("\n Результат %d * %d равен %.0f \n", first_number, second_number, result);

                break;
            }
            case '4':
            {
                printf("\n Введите делимое: ");
                first_number = enter_a_number();

                printf("\n Введите делитель: ");
                second_number = enter_a_number();

                if (second_number == 0)
                {
                    printf("\n Ha нуль делить нельзя! Также не допускайте ввода символов!\n");
                    break;
                }

                result = div(first_number, second_number);
                printf("\n Результат %d / %d равен %.2f \n", first_number, second_number, result);

                break;
            }
            
            case '5':
            {
                printf("\n Вы решили выйти из программы! \n");

                the_fifth_case_is_not_selected = 0;

                break;
            }  
            default:
            {
                printf("\n Такого варианта нет! Попробуйте еще раз. \n");

                break;
            }
        }
    }
    return 0;
}