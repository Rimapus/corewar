/*
** EPITECH PROJECT, 2025
** lfork
** File description:
** Functions to execute the lfork instruction of the corewar
*/

#include "corewar.h"

void execute_lfork(corewar_t *corewar, program_t *program)
{
    short *index = get_memory_slice(corewar->_memory, program->_pc + 1,
        IND_SIZE, 1);

    fork_program(corewar, program, *index);
    free(index);
    program->_pc += 3;
}
