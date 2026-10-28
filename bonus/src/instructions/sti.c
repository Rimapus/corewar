/*
** EPITECH PROJECT, 2025
** sti
** File description:
** Functions to execute the sti instruction of the corewar
*/

#include "corewar.h"

void execute_sti(corewar_t *corewar, program_t *program)
{
    unsigned char coding_byte =
        corewar->_memory[(program->_pc + 1) % MEM_SIZE];
    char source_register = corewar->_memory[(program->_pc + 2) % MEM_SIZE];
    int value_1 = get_param_value(corewar, program, 1);
    int value_2 = get_param_value(corewar, program, 2);
    int new_value;
    int address;

    if (!is_register_valid(source_register)) {
        program->_pc += get_param_increment(coding_byte, 3, 1);
        return;
    }
    new_value = swap_int_endian(program->_registers[source_register - 1]);
    address = (program->_pc + (value_1 + value_2) % IDX_MOD) % MEM_SIZE;
    if (address < 0)
        address += MEM_SIZE;
    paste_memory(corewar->_memory, address, (char *) &new_value, REG_SIZE);
    program->_pc += get_param_increment(coding_byte, 3, 1);
}
