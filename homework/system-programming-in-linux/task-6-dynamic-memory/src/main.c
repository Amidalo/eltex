#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "abonent.h"

int main(void)
{
    struct telephone_directory tel_dir = {
        tel_dir.head = NULL,
        tel_dir.tail= NULL,
        tel_dir.count_of_existing_records = 0,
        tel_dir.next_id = 1

    };
    
    char the_fifth_case_is_not_selected = 1;
    char user_input = 0;

    while (the_fifth_case_is_not_selected)
    {
        print_text_menu();

        scanf(" %c", &user_input);
        clean_stdin(); // Очистка входного буфера stdin из-за '\n'

        switch (user_input)
        {
            case '1':
            {
                if (tel_dir.count_of_existing_records >= MAX_NUMBER_OF_ABONENTS)
                {
                    printf("\n Справочник переполнен, максимум %d записей! \n", MAX_NUMBER_OF_ABONENTS);
                    break;
                }

                char name[MAX_NAME_LENGTH];
                printf("\n Введите имя нового абонента: \n");
                enter_field_with_validation(name, MAX_NAME_LENGTH);

                char second_name[MAX_SECOND_NAME_LENGTH];
                printf("\n Введите фамилию нового абонента: \n");
                enter_field_with_validation(second_name, MAX_SECOND_NAME_LENGTH);

                char tel[MAX_TEL_LENGTH];
                printf("\n Введите телефон нового абонента: \n");
                enter_field_with_validation(tel, MAX_TEL_LENGTH);
                
                add_abonent(&tel_dir, name, second_name, tel);

                break;
            }
            case '2':
            {
                if (tel_dir.head == NULL)
                {
                    printf("\n Справочник пуст, удалять нечего! \n");
                    break;;
                }

                int id_to_delete = 0;

                printf("\n Введите идентификатор того абонента, которого хотите удалить: ");

                scanf(" %d", &id_to_delete);
                clean_stdin(); // Очистка входного буфера stdin из-за '\n' (enter)

                delete_abonent_by_id(&tel_dir, id_to_delete);
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

                find_abonent_by_name(&tel_dir, buffer);
                break;
            }
            case '4':
            {
                if (tel_dir.head == NULL)
                {
                    printf("\n Справочник пуст! \n");
                    break;
                }
                
                print_all_abonents(&tel_dir);
                break;
            }
            
            case '5':
            {
                printf("\n Вы решили выйти из программы! \n");
                free_all_abonents(&tel_dir);
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