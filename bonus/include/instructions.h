/*
** EPITECH PROJECT, 2025
** instructions
** File description:
** Header file for the instructions of corewar
*/

#ifndef _INSTRUCTIONS_H_
    #define _INSTRUCTIONS_H_

    #include "corewar.h"

struct instruction {
    char _code;
    void (*_fct)(corewar_t *corewar, program_t *program);
};

const struct instruction INSTRUCTIONS[] = {
    {0x01, &execute_live},
    {0x02, &execute_ld},
    {0x03, &execute_st},
    {0x04, &execute_add},
    {0x05, &execute_sub},
    {0x06, &execute_and},
    {0x07, &execute_or},
    {0x08, &execute_xor},
    {0x09, &execute_zjmp},
    {0x0a, &execute_ldi},
    {0x0b, &execute_sti},
    {0x0c, &execute_fork},
    {0x0d, &execute_lld},
    {0x0e, &execute_lldi},
    {0x0f, &execute_lfork},
    {0x10, &execute_aff},
    {0x00, NULL}
};

#endif
