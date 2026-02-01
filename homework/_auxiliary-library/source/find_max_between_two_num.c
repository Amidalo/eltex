#include "../algorithms/find_max_between_two_num.h"

int32_t find_max_between_two_num(int32_t first_num, int32_t second_num)
{
    return (first_num > second_num) ? first_num : second_num;
}