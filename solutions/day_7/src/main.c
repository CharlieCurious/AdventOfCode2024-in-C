#include <permutations.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_EQUATIONS 850 

Equation **read_from_file(char *file_name, size_t *total_equations) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        perror("Failed to open file.");
        goto close_file;
    }

    Equation **equations = (Equation **)calloc(NUM_EQUATIONS, sizeof(Equation *));
    if (!equations)
        goto close_file;

    char buffer[80];
    size_t line_index = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        
        char *token, *tokenptr;
        token = strtok_r(buffer, ":", &tokenptr);
        long long result = strtoll(token, NULL, 10);

        long long *numbers = (long long *)malloc(sizeof(long long));
        uint count = 0;
        token = strtok_r(tokenptr, " ", &tokenptr);
        while (token) {
            long long *tmp_numbers = numbers = realloc(numbers, (count + 1) * sizeof(long long));
            if (!tmp_numbers) {
                free(numbers);
                goto free_equations;
            }

            numbers[count++] = strtoll(token, NULL, 10);
            token = strtok_r(NULL, " ", &tokenptr);
        }

        Equation *equation = (Equation *)malloc(sizeof(Equation));
        if (!equation)
            goto free_equations;

        equation->result = result;
        equation->numbers = numbers;
        equation->numbers_count = count;

        equations[line_index++] = equation;
    }
    printf("Read %zu lines\n", line_index + 1);
    *total_equations = line_index;

    fclose(file);
    return equations;

free_equations:
    perror("malloc for equations failed");
    equations_free(equations, NUM_EQUATIONS);


close_file:
    fclose(file);

    return NULL;
}

int main() {
    size_t num_equations;
    Equation **equations = read_from_file("input_files/day_7.txt", &num_equations);
    if (!equations)
        return EXIT_FAILURE;

    long long part_1 = get_possible_permutations_sum(equations, num_equations);

    printf("Part 1: %lld\n", part_1);

    equations_free(equations, NUM_EQUATIONS);
}

