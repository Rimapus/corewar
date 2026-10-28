/*
** EPITECH PROJECT, 2025
** vm
** File description:
** Functions to execute the vm of the corewar
*/

#include "corewar.h"
#include "instructions.h"

static int get_cooldown(corewar_t *corewar, program_t *program)
{
    const op_t *op = find_op_in_tab(corewar->_memory[program->_pc], op_tab);

    if (op == NULL)
        return 0;
    return op->nbr_cycles;
}

static void execute_program(corewar_t *corewar, program_t *program)
{
    for (int i = 0; INSTRUCTIONS[i]._code != 0; i++) {
        if (corewar->_memory[program->_pc] != INSTRUCTIONS[i]._code)
            continue;
        if (program->_cooldown == -1) {
            program->_cooldown = get_cooldown(corewar, program) + 1;
            return;
        }
        if (program->_cooldown != 0)
            return;
        INSTRUCTIONS[i]._fct(corewar, program);
        program->_pc %= MEM_SIZE;
        return;
    }
    program->_pc = (program->_pc + 1) % MEM_SIZE;
}

static void execute_cycle(corewar_t *corewar)
{
    for (program_t *program = corewar->_programs; program != NULL;
        program = program->_next) {
        if (!program->_is_alive)
            continue;
        execute_program(corewar, program);
        if (program->_cooldown != -1)
            program->_cooldown--;
    }
}

static int is_vm_finished(corewar_t *corewar)
{
    if (corewar->_dump_cycle > 1 && corewar->_cycle >= corewar->_dump_cycle)
        return 1;
    if (corewar->_nbr_of_lives >= NBR_LIVE) {
        corewar->_cycle_to_die -= CYCLE_DELTA;
        corewar->_nbr_of_lives = 0;
    }
    if (corewar->_cycle_to_verify >= corewar->_cycle_to_die) {
        check_alive_programs(corewar);
        corewar->_cycle_to_verify = 0;
    }
    if (count_programs(corewar, 1, 1) <= 1)
        return 1;
    return 0;
}

static void dump_memory(corewar_t *corewar)
{
    if (corewar->_dump_cycle == 0)
        return;
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i % 32 == 0 && i != 0)
            my_printf("\n");
        my_printf("%02X", (unsigned char) corewar->_memory[i]);
    }
    my_printf("\n");
}

void start_vm(corewar_t *corewar)
{
    while (!is_vm_finished(corewar)) {
        execute_cycle(corewar);
        corewar->_cycle++;
        corewar->_cycle_to_verify++;
    }
    print_won_message(corewar);
    dump_memory(corewar);
}
