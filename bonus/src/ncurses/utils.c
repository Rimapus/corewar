/*
** EPITECH PROJECT, 2025
** utils
** File description:
** Utilities functions for the ncurses bonus
*/

#include "corewar.h"

void *stop_ncurses(WINDOW *buffer)
{
    clear();
    if (buffer != NULL)
        delwin(buffer);
    if (stdscr != NULL)
        delwin(stdscr);
    endwin();
    return NULL;
}

WINDOW *init_ncurse(void)
{
    WINDOW *buffer;

    if (initscr() == NULL)
        return NULL;
    buffer = newwin(LINES, COLS, 0, 0);
    if (buffer == NULL)
        return stop_ncurses(buffer);
    noecho();
    nodelay(stdscr, TRUE);
    set_escdelay(25);
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_BLACK, COLOR_GREEN);
    init_pair(5, COLOR_BLACK, COLOR_RED);
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);
    return buffer;
}
