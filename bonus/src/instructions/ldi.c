/*
** EPITECH PROJECT, 2025
** ldi
** File description:
** Functions to execute the ldi instruction of the corewar
*/

#include "corewar.h"

void execute_ldi(corewar_t *corewar, program_t *program)
{
    unsigned char coding_byte =
        corewar->_memory[(program->_pc + 1) % MEM_SIZE];
    int value_1 = get_param_value(corewar, program, 0);
    int value_2 = get_param_value(corewar, program, 1);
    int register_increment = get_param_increment(coding_byte, 2, 1);
    int *new_value = get_memory_slice(corewar->_memory,
        program->_pc + (value_1 + value_2) % IDX_MOD, REG_SIZE, 1);

    if (is_register_valid(
        corewar->_memory[(program->_pc + register_increment) % MEM_SIZE])) {
        program->_registers[corewar->_memory
            [(program->_pc + register_increment) % MEM_SIZE] - 1] = *new_value;
        update_carry(program,
            program->_registers[corewar->_memory
                [(program->_pc + register_increment) % MEM_SIZE] - 1]);
    }
    free(new_value);
    program->_pc += register_increment + 1;
}
