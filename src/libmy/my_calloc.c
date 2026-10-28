/*
** EPITECH PROJECT, 2024
** my_calloc
** File description:
** A function that allocates memory and sets every byte to 0
*/

#include "corewar.h"

void *my_calloc(size_t nmemb, size_t size)
{
    void *out = malloc(size * nmemb);
    char *data = NULL;

    if (out == NULL)
        return NULL;
    data = (char *) out;
    for (size_t i = 0; i < size * nmemb; i++)
        data[i] = 0;
    return out;
}
