/*
** EPITECH PROJECT, 2025
** death
** File description:
** Functions for the death detection of corewar
*/

#include "corewar.h"

static void kill_champion_and_forks(corewar_t *corewar, int program_number)
{
    program_t *program = corewar->_programs;

    while (program != NULL) {
        if (program->_number == program_number)
            program->_is_alive = 0;
        program = program->_next;
    }
}

void check_alive_programs(corewar_t *corewar)
{
    program_t *program = corewar->_programs;

    while (program != NULL) {
        if (program->_is_fork) {
            program = program->_next;
            continue;
        }
        if (!program->_is_alive_since_last_check)
            kill_champion_and_forks(corewar, program->_number);
        else
            program->_is_alive_since_last_check = 0;
        program = program->_next;
    }
}
