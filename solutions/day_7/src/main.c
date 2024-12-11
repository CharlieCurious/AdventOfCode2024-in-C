#include <permutations.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_EQUATIONS 850 

Equation **read_from_file(char *file_name) {
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
        int result = atoi(token);

        int *numbers = (int *)malloc(sizeof(int));
        uint count = 0;
        token = strtok_r(tokenptr, " ", &tokenptr);
        while (token) {
            int *tmp_numbers = numbers = realloc(numbers, (count + 1) * sizeof(int));
            if (!tmp_numbers) {
                free(numbers);
                goto free_equations;
            }

            numbers[count++] = atoi(token);
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
    Equation **equations = read_from_file("input_files/day_7.txt");
    if (!equations)
        return EXIT_FAILURE;

    equations_free(equations, NUM_EQUATIONS);
}

