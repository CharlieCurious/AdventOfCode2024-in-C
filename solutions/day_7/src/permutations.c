#include <permutations.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void permutations_generate(
        char **permutations, 
        size_t *count, 
        char *slots, 
        uint n, 
        uint index) {

    if (index == n) {
        permutations[*count] = (char *)malloc((n + 1) * sizeof(char));
        strncpy(permutations[*count], slots, n);
        permutations[*count][n] = '\0';
        (*count)++;
        return;
    }

    slots[index] = '+';
    permutations_generate(permutations, count, slots, n, index + 1);

    slots[index] = '*';
    permutations_generate(permutations, count, slots, n, index + 1);
}

bool has_possible_equation(Equation *equation, char **permutations, size_t permutations_num) {
    long long result;
    for (size_t i = 0; i < permutations_num; i++) {
        char *permutation = permutations[i];
        result = equation->numbers[0];

        for (size_t j = 1; j < equation->numbers_count; j++) {
            if (permutation[j-1] == '+')
                result += equation->numbers[j];
            else
                result *= equation->numbers[j];
        }

        if (result == equation->result)
            return true;
    }

    return false;
}

long long get_possible_permutations_sum(Equation **equations, uint num_equations) {
    long long sum = 0;
    for (size_t i = 0; i < num_equations; i++) {
        Equation *equation = equations[i];
        size_t num_permutations;
        char **permutations = get_permutations_for_equation(equation, &num_permutations);
        if (has_possible_equation(equation, permutations, num_permutations)) {
            sum += equation->result;
        }
    }

    return sum;
}

char **get_permutations_for_equation(Equation *equation, size_t *count) {
    uint n = equation->numbers_count - 1;
    uint num_permutations = 1 << n;
    char **permutations = (char **)malloc(num_permutations * sizeof(char *));
    if (!permutations) 
        return NULL;

    char operands_buffer[num_permutations];
    *count = 0;

    permutations_generate(permutations, count, operands_buffer, n, 0);

    return permutations;
}

void equations_free(Equation **equations, size_t num_equations) {
    for (size_t i = 0; i < num_equations; i++) {
        if (equations[i]) {
            if (equations[i]->numbers)
                free(equations[i]->numbers);
            free(equations[i]);
        }
    }
    free(equations);
}
