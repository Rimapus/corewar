/*
** EPITECH PROJECT, 2025
** ncurses
** File description:
** Ncurses bonus
*/

#include "corewar.h"

static void print_frame(corewar_t *corewar, WINDOW *buffer)
{
    werase(buffer);
    print_infos(buffer, corewar);
    print_memory(buffer, corewar);
    wnoutrefresh(buffer);
    doupdate();
}

static void print_won_message(corewar_t *corewar)
{
    program_t *program = corewar->_programs;
    char *champion_name = "";
    int log_size;
    char *log;

    while (program != NULL) {
        if (program->_number == corewar->_last_live_champion) {
            champion_name = program->_name;
            break;
        }
        program = program->_next;
    }
    log_size = snprintf(NULL, 0, "The player %i(%s) has won.\n",
        corewar->_last_live_champion, champion_name);
    log = my_calloc(log_size + 1, sizeof(char));
    sprintf(log, "The player %i(%s) has won.\n",
        corewar->_last_live_champion, champion_name);
    add_log(corewar, log);
    corewar->_pause = 2;
}

void start_ncurses(corewar_t *corewar)
{
    WINDOW *buffer = init_ncurse();
    clock_t start_time = clock();

    corewar->_speed = 1;
    while (!handle_keypress(corewar)) {
        print_frame(corewar, buffer);
        if (corewar->_pause == 2)
            continue;
        if (!corewar->_pause &&
            clock() - start_time >= CLOCKS_PER_SEC / corewar->_speed) {
            start_time = clock();
            execute_cycle(corewar);
            corewar->_cycle++;
            corewar->_cycle_to_verify++;
        }
        if (is_vm_finished(corewar))
            print_won_message(corewar);
    }
    stop_ncurses(buffer);
}
