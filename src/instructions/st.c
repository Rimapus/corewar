/*
** EPITECH PROJECT, 2025
** st
** File description:
** Functions to execute the st instruction of the corewar
*/

#include "corewar.h"

static void execute_ind_st(corewar_t *corewar, program_t *program,
    int value)
{
    short *indirect_value = get_memory_slice(corewar->_memory,
        program->_pc + 3, IND_SIZE, 1);
    int new_value = swap_int_endian(program->_registers[value - 1]);
    int address = (program->_pc + *indirect_value % IDX_MOD) % MEM_SIZE;

    if (address < 0)
        address += MEM_SIZE;
    paste_memory(corewar->_memory, address, (char *) &new_value, REG_SIZE);
    free(indirect_value);
}

static void execute_reg_st(corewar_t *corewar, program_t *program,
    char source_register)
{
    char dest_register = corewar->_memory[(program->_pc + 3) % MEM_SIZE];

    program->_registers[dest_register - 1] =
        program->_registers[source_register - 1];
}

void execute_st(corewar_t *corewar, program_t *program)
{
    unsigned char coding_byte =
        corewar->_memory[(program->_pc + 1) % MEM_SIZE];
    char source_register = corewar->_memory[(program->_pc + 2) % MEM_SIZE];
    int arg_2_type = get_arg_type(coding_byte, 1);

    if (!is_register_valid(source_register)) {
        program->_pc += get_param_increment(coding_byte, 2, 0);
        return;
    }
    switch (arg_2_type) {
        case T_IND:
            execute_ind_st(corewar, program, source_register);
            break;
        case T_REG:
            execute_reg_st(corewar, program, source_register);
            break;
    }
    program->_pc += get_param_increment(coding_byte, 2, 0);
}
