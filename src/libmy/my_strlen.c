/*
** EPITECH PROJECT, 2025
** my_strlen
** File description:
** A function that return the length of a string
*/

#include "corewar.h"

int my_strlen(char const *str)
{
    int i = 0;

    if (str == NULL)
        return 0;
    while (str[i] != '\0')
        i++;
    return i;
}
