/*
** EPITECH PROJECT, 2025
** memory
** File description:
** Functions to print the memory of corewar in ncurses
*/

#include "corewar.h"

static int is_byte_a_pc(program_t *programs, int index)
{
    program_t *program = programs;

    for (; program != NULL; program = program->_next) {
        if (!program->_is_alive)
            continue;
        if (program->_pc == index)
            return 1;
    }
    return 0;
}

static void set_byte_color(WINDOW *buffer, program_t *programs, int index,
    char value)
{
    if (is_byte_a_pc(programs, index)) {
        if (value == 0)
            wattron(buffer, COLOR_PAIR(3));
        else
            wattron(buffer, COLOR_PAIR(2));
        return;
    }
    if (value == 0)
        return;
    wattron(buffer, COLOR_PAIR(1));
}

void print_memory(WINDOW *buffer, corewar_t *corewar)
{
    int start_column = COLS - (2 * BYTE_PER_LINE);
    int y = 0;
    unsigned char value;

    for (int i = corewar->_memory_offset * BYTE_PER_LINE; i < MEM_SIZE; i++) {
        if (i != corewar->_memory_offset * BYTE_PER_LINE &&
            i % BYTE_PER_LINE == 0)
            y++;
        value = corewar->_memory[i];
        set_byte_color(buffer, corewar->_programs, i, value);
        mvwprintw(buffer, y, start_column + (i % BYTE_PER_LINE) * 2,
            "%02X", value);
        wattrset(buffer, A_NORMAL);
    }
}
