#include <permutations.h>
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
    int result;
    for (size_t i = 0; i < permutations_num; i++) {
        char *permutation = permutations[0];
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
