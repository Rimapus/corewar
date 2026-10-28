/*
** EPITECH PROJECT, 2025
** instructions
** File description:
** Utilities functions for the instruction of corewar
*/

#include "corewar.h"

void update_carry(program_t *program, int value)
{
    if (value == 0)
        program->_carry = 1;
    else
        program->_carry = 0;
}

int get_arg_type(unsigned char coding_byte, int arg_index)
{
    int type = (coding_byte >> (6 - 2 * arg_index)) & 0b11;

    if (type == 0b01)
        return T_REG;
    if (type == 0b10)
        return T_DIR;
    if (type == 0b11)
        return T_IND;
    return 0;
}

char *dup_instruction(char *src, int size)
{
    char *dest = my_calloc(size, sizeof(char));

    for (int i = 0; i < size; i++)
        dest[i] = src[i];
    return dest;
}

int is_register_valid(int register_index)
{
    if (register_index < 1 || register_index > REG_NUMBER)
        return 0;
    return 1;
}
