/*
** EPITECH PROJECT, 2025
** utils
** File description:
** Utilities functions for the corewar
*/

#include "corewar.h"

void swap_endian(void *data, size_t size)
{
    char *data_str = &(*(char *) data);
    char tmp;

    for (size_t i = 0; i < size / 2; i++) {
        tmp = data_str[i];
        data_str[i] = data_str[size - 1 - i];
        data_str[size - 1 - i] = tmp;
    }
}

int swap_int_endian(int value)
{
    int dest = 0;
    char *src = (char *)&value;
    char *dest_ptr = (char *)&dest;

    for (size_t i = 0; i < sizeof(int); i++)
        dest_ptr[i] = src[sizeof(int) - 1 - i];
    return dest;
}

const op_t *find_op_in_tab(char code, const op_t op_tab[])
{
    for (int i = 0; op_tab[i].code != 0; i++) {
        if (op_tab[i].code == code)
            return &op_tab[i];
    }
    return NULL;
}

int is_op_index(char code)
{
    const op_t *op = find_op_in_tab(code, index_tab);

    if (op != NULL)
        return 1;
    return 0;
}

int is_op_long(char code)
{
    if (code == 0x0d || code == 0x0e || code == 0x0f)
        return 1;
    return 0;
}
