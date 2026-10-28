/*
** EPITECH PROJECT, 2025
** sub
** File description:
** Functions to execute the sub instruction of the corewar
*/

#include "corewar.h"

static int handle_errors(char *register_1, char *register_2, char *register_3)
{
    if (!is_register_valid(*register_1) ||
        !is_register_valid(*register_2) ||
        !is_register_valid(*register_3)) {
        free(register_1);
        free(register_2);
        free(register_3);
        return 1;
    }
    return 0;
}

void execute_sub(corewar_t *corewar, program_t *program)
{
    unsigned char coding_byte =
        corewar->_memory[(program->_pc + 1) % MEM_SIZE];
    char *register_1 = get_memory_slice(corewar->_memory,
        program->_pc + 2, 1, 0);
    char *register_2 = get_memory_slice(corewar->_memory,
        program->_pc + 3, 1, 0);
    char *register_3 = get_memory_slice(corewar->_memory,
        program->_pc + 4, 1, 0);

    program->_pc += 5;
    if (coding_byte == 0x54 &&
        !handle_errors(register_1, register_2, register_3)) {
        program->_registers[*register_3 - 1] =
            program->_registers[*register_1 - 1] -
            program->_registers[*register_2 - 1];
        update_carry(program, program->_registers[*register_3 - 1]);
    }
    free(register_1);
    free(register_2);
    free(register_3);
}
