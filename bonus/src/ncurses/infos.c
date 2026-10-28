/*
** EPITECH PROJECT, 2025
** infos
** File description:
** Functions to print the infos of corewar in ncurses
*/

#include "corewar.h"

static void print_title(WINDOW *buffer)
{
    int column = ((COLS - (2 * BYTE_PER_LINE)) - 41) / 2;

    mvwprintw(buffer, 0, column,
        "  _____                                  ");
    mvwprintw(buffer, 1, column,
        " / ____|                                 ");
    mvwprintw(buffer, 2, column,
        "| |     ___  _ __ _____      ____ _ _ __ ");
    mvwprintw(buffer, 3, column,
        "| |    / _ \\| '__/ _ \\ \\ /\\ / / _` | '__|");
    mvwprintw(buffer, 4, column,
        "| |___| (_) | | |  __/\\ V  V / (_| | |   ");
    mvwprintw(buffer, 5, column,
        " \\_____\\___/|_|  \\___| \\_/\\_/ \\__,_|_|   ");
}

void add_log(corewar_t *corewar, char *log)
{
    if (corewar->_logs[LOGS_SIZE - 1] != NULL) {
        free(corewar->_logs[LOGS_SIZE - 1]);
        corewar->_logs[LOGS_SIZE - 1] = NULL;
    }
    for (int i = LOGS_SIZE - 1; i > 0; i--) {
        corewar->_logs[i] = corewar->_logs[i - 1];
    }
    corewar->_logs[0] = log;
}

static void print_logs(WINDOW *buffer, corewar_t *corewar)
{
    wattron(buffer, COLOR_PAIR(3));
    mvwprintw(buffer, LINES - LOGS_SIZE - 1, 0, "Last %i logs:", LOGS_SIZE);
    wattroff(buffer, COLOR_PAIR(3));
    for (int i = 0; i < LOGS_SIZE && corewar->_logs[i] != NULL; i++)
        mvwprintw(buffer, LINES - i - 1, 0, "%s", corewar->_logs[i]);
}

static void print_pause(WINDOW *buffer, corewar_t *corewar)
{
    if (corewar->_pause == 1) {
        wattron(buffer, COLOR_PAIR(6));
        wprintw(buffer, "(PAUSED)");
        wattrset(buffer, A_NORMAL);
    }
    if (corewar->_pause == 2) {
        wattron(buffer, COLOR_PAIR(6));
        wprintw(buffer, "(FINISHED)");
        wattrset(buffer, A_NORMAL);
    }
}

void print_infos(WINDOW *buffer, corewar_t *corewar)
{
    print_title(buffer);
    mvwprintw(buffer, 7, 0, "Cycle: %i ", corewar->_cycle);
    print_pause(buffer, corewar);
    mvwprintw(buffer, 8, 0, "Cycle to die: %4i / %4i",
        corewar->_cycle_to_verify, corewar->_cycle_to_die);
    mvwprintw(buffer, 9, 0, "Number of lives: %2i / %2i",
        corewar->_nbr_of_lives, NBR_LIVE);
    mvwprintw(buffer, 10, 0, "Last live champion: %i",
        corewar->_last_live_champion);
    mvwprintw(buffer, 11, 0, "Speed: %i frame%.*s per second", corewar->_speed,
        corewar->_speed > 1, "s");
    print_champions(corewar, buffer, corewar->_programs, 13);
    print_logs(buffer, corewar);
}
