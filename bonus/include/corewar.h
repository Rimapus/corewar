/*
** EPITECH PROJECT, 2025
** corewar.h
** File description:
** Header file for the corewar
*/

#ifndef _COREWAR_H_
    #define _COREWAR_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <curses.h>
    #include <unistd.h>
    #include <time.h>
    #include "op.h"

    #define BYTE_PER_LINE 64
    #define LOGS_SIZE 15
    #define MIN(a, b) ((a) < (b) ? (a) : (b))
    #define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct program {
    char *_name;
    int _number;
    int _is_fork;
    int _cooldown;
    int _is_alive;
    int _is_alive_since_last_check;
    char *_instructions;
    int _instructions_size;
    int _registers[REG_NUMBER];
    int _pc;
    int _carry;
    struct program *_next;
} program_t;

typedef struct corewar {
    char _memory[MEM_SIZE];
    int _cycle;
    int _cycle_to_die;
    int _cycle_to_verify;
    int _nbr_of_lives;
    int _last_live_champion;
    int _dump_cycle;
    program_t *_programs;
    int _speed;
    int _pause;
    int _memory_offset;
    char *_logs[LOGS_SIZE];
} corewar_t;

/* NCURSES */
WINDOW *init_ncurse(void);
void start_ncurses(corewar_t *corewar);
void *stop_ncurses(WINDOW *buffer);
int handle_keypress(corewar_t *corewar);
void add_log(corewar_t *corewar, char *log);
void print_infos(WINDOW *buffer, corewar_t *corewar);
void print_memory(WINDOW *buffer, corewar_t *corewar);
void print_champions(corewar_t *corewar, WINDOW *buffer, program_t *champion,
    int champion_line);

/* PARSING */
int parse_input(corewar_t *corewar, char **argv);

/* CHAMPIONS */
program_t *get_champion(char *champion_path);

/* PROGRAMS */
void add_program(corewar_t *corewar, program_t *program);
int count_programs(corewar_t *corewar, int champions_only, int alive_only);

/* MEMORY */
void paste_memory(char *destination, int index, char *source, int source_size);
void load_programs(corewar_t *corewar);
void *get_memory_slice(char *memory, int start, int size, int swap);

/* VM */
void execute_cycle(corewar_t *corewar);
int is_vm_finished(corewar_t *corewar);

/* VALUES */
int get_param_increment(unsigned char coding_byte, int param_index,
    int is_index);
int get_param_value(corewar_t *corewar, program_t *program, int param_index);

/* INSTRUCTIONS */
void update_carry(program_t *program, int value);
int get_arg_type(unsigned char coding_byte, int arg_index);
char *dup_instruction(char *src, int size);
int is_register_valid(int register_index);
void execute_live(corewar_t *corewar, program_t *program);
void execute_ld(corewar_t *corewar, program_t *program);
void execute_st(corewar_t *corewar, program_t *program);
void execute_add(corewar_t *corewar, program_t *program);
void execute_sub(corewar_t *corewar, program_t *program);
void execute_and(corewar_t *corewar, program_t *program);
void execute_or(corewar_t *corewar, program_t *program);
void execute_xor(corewar_t *corewar, program_t *program);
void execute_zjmp(corewar_t *corewar, program_t *program);
void execute_ldi(corewar_t *corewar, program_t *program);
void execute_sti(corewar_t *corewar, program_t *program);
void fork_program(corewar_t *corewar, program_t *program, int pc_increment);
void execute_fork(corewar_t *corewar, program_t *program);
void execute_lld(corewar_t *corewar, program_t *program);
void execute_lldi(corewar_t *corewar, program_t *program);
void execute_lfork(corewar_t *corewar, program_t *program);
void execute_aff(corewar_t *corewar, program_t *program);

/* DEATH */
void check_alive_programs(corewar_t *corewar);

/* UTILS */
void swap_endian(void *data, size_t size);
int swap_int_endian(int value);
const op_t *find_op_in_tab(char code, const op_t op_tab[]);
int is_op_index(char code);
int is_op_long(char code);

/* FREE */
void free_program(program_t *program);
void *free_champion(program_t *program, header_t *header);
void free_corewar(corewar_t *corewar);

/* LIBMY */
int my_printf(char *str, ...);
void *my_calloc(size_t nmemb, size_t size);
int my_strlen(char const *str);
char *my_strdup(char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_getnbr(char const *str);
int my_str_isnum(char const *str);

#endif
