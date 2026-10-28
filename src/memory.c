/*
** EPITECH PROJECT, 2025
** memory
** File description:
** Functions to manipulate the memory of corewar
*/

#include "corewar.h"

void paste_memory(char *destination, int index, char *source, int source_size)
{
    for (int i = 0; i < source_size; i++)
        destination[index + i] = source[i];
}

static void load_program(corewar_t *corewar, program_t *program)
{
    if (program == NULL)
        return;
    load_program(corewar, program->_next);
    paste_memory(corewar->_memory, program->_pc, program->_instructions,
        program->_instructions_size);
}

void load_programs(corewar_t *corewar)
{
    load_program(corewar, corewar->_programs);
}

void *get_memory_slice(char *memory, int start, int size, int swap)
{
    char *slice = my_calloc(1, size);

    for (int i = 0; i < size; i++)
        slice[i] = memory[(start + i) % MEM_SIZE];
    if (swap)
        swap_endian(slice, size);
    return slice;
}
