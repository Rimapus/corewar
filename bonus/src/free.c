/*
** EPITECH PROJECT, 2025
** parsing
** File description:
** Functions to parse informations about a .cor champion
*/

#include "corewar.h"

void free_program(program_t *program)
{
    if (program == NULL)
        return;
    free(program->_name);
    free(program->_instructions);
    free(program);
}

void *free_champion(program_t *program, header_t *header)
{
    free_program(program);
    if (header != NULL)
        free(header);
    return NULL;
}

static void free_logs(corewar_t *corewar)
{
    for (int i = 0; i < LOGS_SIZE && corewar->_logs[i] != NULL; i++) {
        free(corewar->_logs[i]);
        corewar->_logs[i] = NULL;
    }
}

void free_corewar(corewar_t *corewar)
{
    program_t *program = corewar->_programs;
    program_t *next;

    while (program != NULL) {
        next = program->_next;
        free_program(program);
        program = next;
    }
    free_logs(corewar);
    free(corewar);
}
