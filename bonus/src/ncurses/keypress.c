/*
** EPITECH PROJECT, 2025
** keypress
** File description:
** Functions to handle the keypresses of the ncurses window of corewar
*/

#include "corewar.h"

static int handle_ch(corewar_t *corewar, int ch)
{
    if (ch == 'q' || ch == 27)
        return 1;
    if (ch == KEY_UP)
        corewar->_memory_offset = MAX(0, corewar->_memory_offset - 1);
    if (ch == KEY_DOWN)
        corewar->_memory_offset = MIN(MEM_SIZE / BYTE_PER_LINE - LINES,
            corewar->_memory_offset + 1);
    if (ch == KEY_LEFT)
        corewar->_speed = MAX(1, corewar->_speed / 2);
    if (ch == KEY_RIGHT)
        corewar->_speed = MIN(8192, corewar->_speed * 2);
    if (ch == ' ') {
        if (corewar->_pause == 2)
            return 0;
        corewar->_pause = !corewar->_pause;
    }
    return 0;
}

int handle_keypress(corewar_t *corewar)
{
    int return_value = 0;
    int ch = getch();

    while (ch != ERR) {
        if (handle_ch(corewar, ch))
            return_value = 1;
        ch = getch();
    }
    return return_value;
}
