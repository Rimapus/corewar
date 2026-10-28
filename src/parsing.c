/*
** EPITECH PROJECT, 2025
** parsing
** File description:
** Functions to parse the user input of corewar
*/

#include "corewar.h"

static int parse_dump(corewar_t *corewar, char **argv, int *arg_index)
{
    if (my_strcmp(argv[*arg_index], "-dump") != 0)
        return 0;
    if (argv[*arg_index + 1] == NULL)
        return 1;
    if (!my_str_isnum(argv[*arg_index + 1]))
        return 1;
    corewar->_dump_cycle = my_getnbr(argv[*arg_index + 1]) + 1;
    if (corewar->_dump_cycle < 0)
        return 1;
    *arg_index += 2;
    return 0;
}

static int parse_options(char **argv, int *arg_index,
    int *champion_number, int *champion_address)
{
    int value;

    if (my_strcmp(argv[*arg_index], "-n") != 0 &&
        my_strcmp(argv[*arg_index], "-a") != 0)
        return 1;
    if (argv[*arg_index + 1] == NULL)
        return 1;
    if (!my_str_isnum(argv[*arg_index + 1]))
        return 1;
    value = my_getnbr(argv[*arg_index + 1]);
    if (value < 0)
            return 1;
    if (my_strcmp(argv[*arg_index], "-n") == 0)
        *champion_number = value;
    if (my_strcmp(argv[*arg_index], "-a") == 0)
        *champion_address = value % MEM_SIZE;
    *arg_index += 2;
    return 0;
}

static void set_champion_variables(program_t *champion, int champion_number,
    int champion_address)
{
    champion->_number = champion_number;
    champion->_registers[0] = champion_number;
    champion->_pc = champion_address;
    champion->_cooldown = -1;
    champion->_is_alive = 1;
    champion->_carry = 1;
}

static program_t *parse_champion(char **argv, int *arg_index,
    int champion_number)
{
    int champion_address = -1;
    program_t *champion;

    while (argv[*arg_index] != NULL && argv[*arg_index][0] == '-') {
        if (parse_options(argv, arg_index,
            &champion_number, &champion_address))
            return NULL;
    }
    if (argv[*arg_index] == NULL)
        return NULL;
    champion = get_champion(argv[*arg_index]);
    if (champion == NULL)
        return NULL;
    set_champion_variables(champion, champion_number, champion_address);
    return champion;
}

static void add_missing_pcs(corewar_t *corewar)
{
    int index_increment = MEM_SIZE / count_programs(corewar, 1, 0);
    int index = 0;
    program_t *champion = corewar->_programs;

    while (champion != NULL) {
        if (champion->_pc == -1)
            champion->_pc = index;
        index += index_increment;
        champion = champion->_next;
    }
}

static int parse_champions(corewar_t *corewar, char **argv, int *arg_index)
{
    int champion_number = 1;
    program_t *champion;

    while (argv[*arg_index] != NULL) {
        champion = parse_champion(argv, arg_index, champion_number);
        if (champion == NULL)
            return 1;
        add_program(corewar, champion);
        champion_number++;
        (*arg_index)++;
    }
    add_missing_pcs(corewar);
    return 0;
}

int parse_input(corewar_t *corewar, char **argv)
{
    int arg_index = 1;
    int champion_count;

    if (argv[arg_index] == NULL)
        return 1;
    if (parse_dump(corewar, argv, &arg_index))
        return 1;
    if (parse_champions(corewar, argv, &arg_index))
        return 1;
    champion_count = count_programs(corewar, 1, 0);
    if (champion_count < 2 || champion_count > 4)
        return 1;
    corewar->_cycle_to_die = CYCLE_TO_DIE;
    return 0;
}
