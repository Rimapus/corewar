/*
** EPITECH PROJECT, 2025
** zjmp
** File description:
** Functions to execute the zjmp instruction of the corewar
*/

#include "corewar.h"

void execute_zjmp(corewar_t *corewar, program_t *program)
{
    short *index;

    if (program->_carry) {
        index = get_memory_slice(corewar->_memory, program->_pc + 1,
            IND_SIZE, 1);
        program->_pc += *index % IDX_MOD;
        free(index);
    } else
        program->_pc += 3;
}
