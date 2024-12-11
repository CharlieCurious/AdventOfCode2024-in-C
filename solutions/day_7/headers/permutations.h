#pragma once

#include <stdbool.h>
#include <sys/types.h>

typedef struct Equation {
    int result;
    int *numbers;
    size_t numbers_count;
} Equation;

void permutations_generate(char **permutations, size_t *count, char *slots, uint n, uint index);
bool has_possible_equation(Equation *equation, char **permutations, size_t permutations_num);
void equations_free(Equation **equations, size_t num_equations);


