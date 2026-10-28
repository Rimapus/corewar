/*
** EPITECH PROJECT, 2025
** live
** File description:
** Functions to execute the live instruction of the corewar
*/

#include "corewar.h"

static void set_alive(corewar_t *corewar, int program_number)
{
    program_t *program = corewar->_programs;

    for (; program != NULL; program = program->_next) {
        if (program->_is_fork || program->_number != program_number)
            continue;
        program->_is_alive_since_last_check = 1;
        corewar->_last_live_champion = program->_number;
        break;
    }
}

void execute_live(corewar_t *corewar, program_t *program)
{
    int *champion_number = get_memory_slice(corewar->_memory,
        program->_pc + 1, DIR_SIZE, 1);
    int log_size = snprintf(NULL, 0, "The player %i(%s) is alive.\n",
        *champion_number, program->_name);
    char *log = my_calloc(log_size + 1, sizeof(char));

    sprintf(log, "The player %i(%s) is alive.\n",
        *champion_number, program->_name);
    add_log(corewar, log);
    set_alive(corewar, *champion_number);
    corewar->_nbr_of_lives++;
    free(champion_number);
    program->_pc += 5;
}
