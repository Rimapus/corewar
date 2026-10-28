/*
** EPITECH PROJECT, 2025
** champions
** File description:
** Functions to parse informations about a .cor champion
*/

#include "corewar.h"

static void handle_type(unsigned char type, char op_code, int *op_size)
{
    switch (type) {
    case 1:
        *op_size += 1;
        break;
    case 2:
        if (is_op_index(op_code))
            *op_size += IND_SIZE;
        else
            *op_size += DIR_SIZE;
        break;
    case 3:
        *op_size += IND_SIZE;
        break;
    }
}

static int handle_parameters(FILE *file, char op_code,
    unsigned char coding_byte)
{
    unsigned char type;
    int op_size = 0;
    int old_op_size = 0;

    for (int i = 3; i >= 0; i--) {
        old_op_size = op_size;
        type = (coding_byte >> (i * 2)) & 0b11;
        handle_type(type, op_code, &op_size);
        fseek(file, op_size - old_op_size, SEEK_CUR);
    }
    return op_size;
}

static int handle_index_op(FILE *file, char op_code, int *op_size)
{
    if (op_code != 1 && op_code != 9 && op_code != 12 && op_code != 15)
        return 1;
    switch (op_code) {
    case 1:
        *op_size = DIR_SIZE;
        break;
    case 9:
    case 12:
    case 15:
        *op_size = IND_SIZE;
        break;
    }
    fseek(file, *op_size, SEEK_CUR);
    return 0;
}

static int handle_op(FILE *file, char op_code, int *op_size, int *program_size)
{
    unsigned char coding_byte = 0;

    if (!handle_index_op(file, op_code, op_size))
        return 0;
    if (fread(&coding_byte, 1, 1, file) == 0)
        return 1;
    (*program_size)++;
    *op_size = handle_parameters(file, op_code, coding_byte);
    return 0;
}

static void fill_instructions(FILE *file, header_t *header, program_t *program)
{
    fseek(file, -header->prog_size, SEEK_CUR);
    program->_instructions = my_calloc(header->prog_size, sizeof(char));
    fread(program->_instructions, 1, header->prog_size, file);
    program->_instructions_size = header->prog_size;
}

static int parse_instructions(FILE *file, header_t *header, program_t *program)
{
    int program_size = 0;
    char op_code;
    const op_t *op;
    int op_size;

    while (fread(&op_code, 1, 1, file) != 0) {
        op = find_op_in_tab(op_code, op_tab);
        if (op == NULL)
            return 1;
        program_size++;
        if (handle_op(file, op_code, &op_size, &program_size))
            return 1;
        program_size += op_size;
    }
    if (header->prog_size != program_size)
        return 1;
    fill_instructions(file, header, program);
    return 0;
}

static header_t *parse_header(FILE *file, program_t *program)
{
    header_t *header = my_calloc(1, sizeof(header_t));

    if (header == NULL)
        return NULL;
    fread(header, sizeof(header_t), 1, file);
    header->magic = swap_int_endian(header->magic);
    header->prog_size = swap_int_endian(header->prog_size);
    if (header->magic != COREWAR_EXEC_MAGIC) {
        free(header);
        return NULL;
    }
    program->_name = my_strdup(header->prog_name);
    return header;
}

program_t *get_champion(char *champion_path)
{
    FILE *file;
    program_t *program;
    header_t *header;

    file = fopen(champion_path, "rb");
    if (file == NULL)
        return NULL;
    program = my_calloc(1, sizeof(program_t));
    header = parse_header(file, program);
    if (header == NULL) {
        fclose(file);
        return free_champion(program, header);
    }
    if (parse_instructions(file, header, program)) {
        fclose(file);
        return free_champion(program, header);
    }
    free(header);
    fclose(file);
    return program;
}
