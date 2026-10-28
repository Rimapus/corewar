/*
** EPITECH PROJECT, 2025
** my_str_isnum
** File description:
** A function that returns 1 if the string only contains digits and 0 otherwise
*/

#include "corewar.h"

int my_str_isnum(char const *str)
{
    if (my_strlen(str) == 0)
        return 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 48 || str[i] > 57) {
            return 0;
        }
    }
    return 1;
}
