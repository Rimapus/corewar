/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** A function that allocates memory and
** copies the string given as argument in it
*/

#include "corewar.h"

char *my_strdup(char const *src)
{
    int src_len = my_strlen(src);
    char *dest;
    int i = 0;

    dest = my_calloc(src_len + 1, sizeof(char));
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
