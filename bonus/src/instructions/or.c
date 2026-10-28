/*
** EPITECH PROJECT, 2025
** or
** File description:
** Functions to execute the or instruction of the corewar
*/

#include "corewar.h"

void execute_or(corewar_t *corewar, program_t *program)
{
    unsigned char coding_byte =
        corewar->_memory[(program->_pc + 1) % MEM_SIZE];
    int value_1 = get_param_value(corewar, program, 0);
    int value_2 = get_param_value(corewar, program, 1);
    int register_increment = get_param_increment(coding_byte, 2, 0);

    if (!is_register_valid(
        corewar->_memory[(program->_pc + register_increment) % MEM_SIZE])) {
        program->_pc += register_increment + 1;
        return;
    }
    program->_registers[corewar->_memory
        [(program->_pc + register_increment) % MEM_SIZE] - 1] =
        value_1 | value_2;
    update_carry(program,
        program->_registers[corewar->_memory
            [(program->_pc + register_increment) % MEM_SIZE] - 1]);
    program->_pc += register_increment + 1;
}
