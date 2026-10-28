/*
** EPITECH PROJECT, 2025
** fork
** File description:
** Functions to execute the fork instruction of the corewar
*/

#include "corewar.h"

void fork_program(corewar_t *corewar, program_t *program, int pc_increment)
{
    program_t *new_fork = my_calloc(1, sizeof(program_t));

    new_fork->_name = my_strdup(program->_name);
    new_fork->_number = program->_number;
    new_fork->_is_fork = 1;
    new_fork->_cooldown = program->_cooldown;
    new_fork->_is_alive = program->_is_alive;
    new_fork->_is_alive_since_last_check =
        program->_is_alive_since_last_check;
    new_fork->_instructions = dup_instruction(program->_instructions,
        program->_instructions_size);
    new_fork->_instructions_size = program->_instructions_size;
    for (int i = 0; i < REG_NUMBER; i++)
        new_fork->_registers[i] = program->_registers[i];
    new_fork->_pc = program->_pc + pc_increment;
    new_fork->_carry = program->_carry;
    add_program(corewar, new_fork);
}

void execute_fork(corewar_t *corewar, program_t *program)
{
    short *index = get_memory_slice(corewar->_memory, program->_pc + 1,
        IND_SIZE, 1);

    fork_program(corewar, program, *index % IDX_MOD);
    free(index);
    program->_pc += 3;
}
