#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "utils.h"
#include "abonent.h"

int main(void)
{
    struct abonent abonents[MAX_NUMBER_OF_ABONENTS] = { 0 };
    
    int8_t the_fifth_case_is_not_selected = 1;
    int8_t user_input = 0;
    int8_t count_of_existing_records = 0;

    while (the_fifth_case_is_not_selected)
    {
        print_text_menu();

        scanf(" %c", &user_input);
        clean_stdin(); // Очистка входного буфера stdin из-за '\n'

        switch (user_input)
        {
            case '1':
            {
                if (count_of_existing_records >= MAX_NUMBER_OF_ABONENTS)
                {
                    printf("\n Справочник переполнен, максимум %d записей! \n", MAX_NUMBER_OF_ABONENTS);
                    break;
                }
                
                add_abonent(&abonents[count_of_existing_records], &count_of_existing_records);
                break;
            }
            case '2':
            {
                if (count_of_existing_records < 1)
                {
                    printf("\n Справочник пуст, удалять нечего! \n");
                    break;;
                }

                printf("\n Введите индекс того абонента, которого хотите удалить: ");
                scanf(" %hhd", &user_input);
                clean_stdin(); // Очистка входного буфера stdin из-за '\n' (enter)

                delete_abonent_by_index(abonents, &count_of_existing_records, user_input);
                break;
            }
            case '3':
            {
                char buffer[MAX_NAME_LENGTH];
                printf("\n Внимание, максимум 9 символов! \n");
                printf("\n Введите имя, по которому будем искать: ");

                if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;

                buffer[strcspn(buffer, "\n")] = '\0';
                size_t length = strlen(buffer);

                if (length > 0 && buffer[length - 1] == '\n')
                {
                    buffer[length - 1] == '\0';
                }
                else if (length == MAX_NAME_LENGTH - 1)
                {
                    printf("\n Вы превысили лимит! Имя обрезано до %d символов \n", MAX_NAME_LENGTH - 1);
                    clean_stdin(); // Очистка буфера стандартного ввода stdin от предыдущего ввода пользователем
                }

                find_all_abonents_by_name(abonents, &count_of_existing_records, buffer);
                break;
            }
            case '4':
            {
                print_all_abonents(abonents, &count_of_existing_records);
                break;
            }
            
            case '5':
            {
                printf("\n Вы решили выйти из программы! \n");
                return 0;
            }  
            default:
            {
                printf("\n Такого варианта нет! Попробуйте еще раз. \n");
                break;
            }
        }
    }
}
