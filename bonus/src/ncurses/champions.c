/*
** EPITECH PROJECT, 2025
** champions
** File description:
** Functions to print the champions of corewar in ncurses
*/

#include "corewar.h"

static int count_forks(corewar_t *corewar, program_t *champion)
{
    int forks = 0;

    for (program_t *program = corewar->_programs; program != NULL;
        program = program->_next) {
        if (program->_number != champion->_number || !program->_is_fork)
            continue;
        forks++;
    }
    return forks;
}

static void print_registers(WINDOW *buffer, program_t *champion, int line)
{
    mvwprintw(buffer, line, 0, "Registers:\n[");
    for (int i = 0; i < REG_NUMBER; i++) {
        wprintw(buffer, "%i", champion->_registers[i]);
        if (i != REG_NUMBER - 1)
            wprintw(buffer, ", ");
        else
            wprintw(buffer, "]");
    }
}

static void print_champion(corewar_t *corewar, WINDOW *buffer,
    program_t *champion, int line)
{
    int fork_count;

    mvwprintw(buffer, line, 0, "%s (%i), ", champion->_name,
        champion->_number);
    if (champion->_is_alive) {
        wattron(buffer, COLOR_PAIR(4));
        wprintw(buffer, "Alive");
    } else {
        wattron(buffer, COLOR_PAIR(5));
        wprintw(buffer, "Dead");
    }
    wattrset(buffer, A_NORMAL);
    fork_count = count_forks(corewar, champion);
    wprintw(buffer, ", %i fork%.*s", fork_count, fork_count > 1, "s");
    print_registers(buffer, champion, line + 1);
    mvwprintw(buffer, line + 3, 0, "PC: %i, Carry: %i, Cooldown: %i",
        champion->_pc, champion->_carry, champion->_cooldown);
}

void print_champions(corewar_t *corewar, WINDOW *buffer, program_t *programs,
    int champion_line)
{
    wattron(buffer, COLOR_PAIR(3));
    mvwprintw(buffer, champion_line, 0, "Champions:");
    wattroff(buffer, COLOR_PAIR(3));
    champion_line++;
    for (program_t *program = programs; program != NULL;
        program = program->_next) {
        if (program->_is_fork)
            continue;
        print_champion(corewar, buffer, program, champion_line);
        champion_line += 5;
    }
}
