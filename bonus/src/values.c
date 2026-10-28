/*
** EPITECH PROJECT, 2025
** values
** File description:
** Functions to get values in the memory of corewar
*/

#include "corewar.h"

int get_param_increment(unsigned char coding_byte, int param_index,
    int is_index)
{
    int index = 0;
    int increment = 2;
    int type;

    while (index < param_index) {
        type = get_arg_type(coding_byte, index);
        switch (type) {
            case T_REG:
                increment += 1;
                break;
            case T_DIR:
                increment += is_index ? IND_SIZE : DIR_SIZE;
                break;
            case T_IND:
                increment += IND_SIZE;
                break;
        }
        index++;
    }
    return increment;
}

static int get_dir_value(corewar_t *corewar, int address, int is_index)
{
    int return_value = 0;
    short *ind_size_value;
    int *dir_size_value;

    if (is_index) {
        ind_size_value = get_memory_slice(corewar->_memory, address,
            IND_SIZE, 1);
        return_value = *ind_size_value;
        free(ind_size_value);
    } else {
        dir_size_value = get_memory_slice(corewar->_memory, address,
            DIR_SIZE, 1);
        return_value = *dir_size_value;
        free(dir_size_value);
    }
    return return_value;
}

static int get_ind_index_value(corewar_t *corewar, int new_address)
{
    int return_value = 0;
    int *dir_size_value = get_memory_slice(corewar->_memory,
        new_address, DIR_SIZE, 1);

    return_value = *dir_size_value;
    free(dir_size_value);
    return return_value;
}

static int get_ind_value(corewar_t *corewar, program_t *program, int address,
    int is_index)
{
    int return_value = 0;
    int is_long = is_op_long(corewar->_memory[program->_pc]);
    short *indirect = get_memory_slice(corewar->_memory, address,
        IND_SIZE, 1);
    short *ind_size_value;
    int new_address = program->_pc +
        (is_long ? *indirect : (*indirect % IDX_MOD));

    if (new_address < 0)
        new_address += MEM_SIZE;
    if (is_index) {
        ind_size_value = get_memory_slice(corewar->_memory,
            new_address, IND_SIZE, 1);
        return_value = *ind_size_value;
        free(ind_size_value);
    } else
        return_value = get_ind_index_value(corewar, new_address);
    free(indirect);
    return return_value;
}

static int get_address_value(corewar_t *corewar, program_t *program,
    int address, int type)
{
    int is_index = is_op_index(corewar->_memory[program->_pc]);
    int return_value = 0;

    switch (type) {
        case T_REG:
            if (!is_register_valid(corewar->_memory[address]))
                return_value = 0;
            return_value = program->_registers[corewar->_memory[address] - 1];
            break;
        case T_DIR:
            return_value = get_dir_value(corewar, address, is_index);
            break;
        case T_IND:
            return_value = get_ind_value(corewar, program, address, is_index);
            break;
    }
    return return_value;
}

int get_param_value(corewar_t *corewar, program_t *program, int param_index)
{
    int is_index = is_op_index(corewar->_memory[program->_pc]);
    unsigned char coding_byte = corewar->_memory[program->_pc + 1];
    int increment = get_param_increment(coding_byte, param_index, is_index);
    int type = get_arg_type(coding_byte, param_index);

    return get_address_value(corewar, program, program->_pc + increment, type);
}
