#pragma once

#include <stdbool.h>
#include <sys/types.h>

typedef struct Equation {
    long long result;
    long long *numbers;
    size_t numbers_count;
} Equation;

void permutations_generate(char **permutations, size_t *count, char *slots, uint n, uint index);
bool has_possible_equation(Equation *equation, char **permutations, size_t permutations_num);
long long get_possible_permutations_sum(Equation **equations, uint num_equations);
char **get_permutations_for_equation(Equation *equation, size_t *count);
void equations_free(Equation **equations, size_t num_equations);


