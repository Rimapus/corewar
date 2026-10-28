/*
** EPITECH PROJECT, 2025
** programs
** File description:
** Functions to manipulate the programs of corewar
*/

#include "corewar.h"

void add_program(corewar_t *corewar, program_t *program)
{
    program_t *current = corewar->_programs;
    program_t *previous = NULL;

    if (corewar->_programs == NULL) {
        corewar->_programs = program;
        program->_next = NULL;
        return;
    }
    while (current != NULL && current->_number < program->_number) {
        previous = current;
        current = current->_next;
    }
    if (previous == NULL) {
        program->_next = corewar->_programs;
        corewar->_programs = program;
        return;
    }
    program->_next = current;
    previous->_next = program;
}

int count_programs(corewar_t *corewar, int champions_only, int alive_only)
{
    int count = 0;
    program_t *program = corewar->_programs;

    while (program != NULL) {
        if (!(champions_only && program->_is_fork) &&
            !(alive_only && !program->_is_alive))
            count++;
        program = program->_next;
    }
    return count;
}
