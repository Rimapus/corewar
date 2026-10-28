/*
** EPITECH PROJECT, 2025
** main
** File description:
** The main functions of corewar
*/

#include "corewar.h"

static int print_help(int return_value)
{
    my_printf("USAGE\n");
    my_printf("\t./corewar [-dump nbr_cycle] [[-n prog_number] "
        "[-a load_address] prog_name] ...");
    my_printf("DESCRIPTION\n");
    my_printf("\t-dump\t\tnbr_cycle dumps the memory after the nbr_cycle "
        "execution (if the round isn't already over) with the following "
        "format: 32 bytes/line in hexadecimal (A0BCDEFE1DD3...)\n");
    my_printf("\t-n\t\tprog_number sets the next program's number. By "
        "default, the first free number in the parameter order\n");
    my_printf("\t-a\t\tload_address sets the next program's loading address. "
        "When no address is specified, optimize the addresses so that the "
        "processes are as far away from each other as possible. The addresses "
        "are MEM_SIZE modulo.\n");
    return return_value;
}

int main(int argc __attribute__((unused)), char **argv)
{
    corewar_t *corewar = my_calloc(1, sizeof(corewar_t));

    if (corewar == NULL)
        return 84;
    if (my_strcmp(argv[1], "-h") == 0 || my_strcmp(argv[1], "--help") == 0)
        return print_help(0);
    if (parse_input(corewar, argv)) {
        free_corewar(corewar);
        return print_help(84);
    }
    load_programs(corewar);
    start_vm(corewar);
    free_corewar(corewar);
    return 0;
}
