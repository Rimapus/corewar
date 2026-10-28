/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** A function that return a number sent as a string
*/

static int is_numerical(char character)
{
    if (character >= 48 && character <= 57)
        return 1;
    return 0;
}

static int process_chr(char chr, long *res, int *negate_cnt)
{
    if (is_numerical(chr) == 1) {
        if ((*res) * 10 > 2147483648)
            return -1;
        (*res) *= 10;
        (*res) += chr - 48;
    }
    if (is_numerical(chr) == 0) {
        if (chr == '-') {
            (*negate_cnt)++;
        }
        if (chr != '-' && chr != '+') {
            return 1;
        }
    }
    return 0;
}

static int check_overflow_and_negate(long result, int negate_count)
{
    if (negate_count % 2 == 1) {
        if (- result < -2147483648)
            return 0;
        result = -result;
    }
    if (negate_count % 2 == 0) {
        if (result > 2147483647)
            return 0;
    }
    return result;
}

int my_getnbr(char const *str)
{
    int i = 0;
    long res = 0;
    int negate_count = 0;
    int is_finished = 0;
    int process_out = 0;

    while (is_finished == 0 && str[i]) {
        process_out = process_chr(str[i], &res, &negate_count);
        if (process_out == -1)
            return 0;
        if (process_out == 1)
            is_finished = 1;
        i++;
    }
    return check_overflow_and_negate(res, negate_count);
}
