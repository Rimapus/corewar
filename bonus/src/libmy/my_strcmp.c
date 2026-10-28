/*
** EPITECH PROJECT, 2025
** my_strcmp
** File description:
** A function that compares two strings and returns the difference
*/

#include "corewar.h"

int my_strcmp(char const *s1, char const *s2)
{
    int s1_len = my_strlen(s1);
    int s2_len = my_strlen(s2);
    int i = 0;

    while (i < s1_len || i < s2_len) {
        if (i >= s1_len)
            return - s2[i];
        if (i >= s2_len)
            return s1[i];
        if (s1[i] - s2[i] != 0)
            return s1[i] - s2[i];
        i++;
    }
    return 0;
}
