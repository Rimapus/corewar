/*
** EPITECH PROJECT, 2025
** aff
** File description:
** Functions to execute the aff instruction of the corewar
*/

#include "corewar.h"

void execute_aff(corewar_t *corewar, program_t *program)
{
    unsigned char coding_byte =
        corewar->_memory[(program->_pc + 1) % MEM_SIZE];
    char *register_index = get_memory_slice(corewar->_memory,
        program->_pc + 2, 1, 0);
    char *log = my_calloc(3, sizeof(char));

    log[1] = '\n';
    program->_pc += 3;
    if (coding_byte != 0x40 ||
        !is_register_valid(*register_index)) {
        add_log(corewar, log);
        free(register_index);
        return;
    }
    log[0] = program->_registers[*register_index - 1] % 256;
    add_log(corewar, log);
    free(register_index);
}
