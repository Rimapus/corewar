/*
** EPITECH PROJECT, 2025
** lld
** File description:
** Functions to execute the lld instruction of the corewar
*/

#include "corewar.h"

void execute_lld(corewar_t *corewar, program_t *program)
{
    unsigned char coding_byte =
        corewar->_memory[(program->_pc + 1) % MEM_SIZE];
    int value = get_param_value(corewar, program, 0);
    int register_increment = get_param_increment(coding_byte, 1, 0);

    if (!is_register_valid(
        corewar->_memory[(program->_pc + register_increment) % MEM_SIZE])) {
        program->_pc += register_increment + 1;
        return;
    }
    program->_registers[corewar->_memory
        [(program->_pc + register_increment) % MEM_SIZE] - 1] = value;
    update_carry(program,
        program->_registers[corewar->_memory
            [(program->_pc + register_increment) % MEM_SIZE] - 1]);
    program->_pc += register_increment + 1;
}
