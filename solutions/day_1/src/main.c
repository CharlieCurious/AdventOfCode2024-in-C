#include <dictionary.h>
#include <file_parser.h>
#include <stdlib.h>

#define INPUT_LINES_COUNT 1000

static int qsort_compare(const void *a, const void *b);

int main() {
    FILE *file = open_input_file("input_files/day_1.txt"); 
    if (file == NULL) exit(EXIT_FAILURE);

    InputLines *input_lines = (InputLines *)malloc(sizeof(InputLines));
    read_input_lines(file, input_lines);
    fclose(file);

    unsigned int left_col[INPUT_LINES_COUNT];
    unsigned int right_col[INPUT_LINES_COUNT];

    Dictionary *multipliers = create_dictionary(1000);

    for (unsigned int i = 0; i < INPUT_LINES_COUNT; i++) {
        unsigned int left_num, right_num;
        sscanf(input_lines->lines[i], "%u %u", &left_num, &right_num);
        
        left_col[i] = left_num;
        right_col[i] = right_num;

        unsigned int occurence_count = 0;
        find(multipliers, right_num, &occurence_count);
        insert_in_dictionary(multipliers, right_num, ++occurence_count);
    }

    qsort(left_col, INPUT_LINES_COUNT, sizeof(unsigned int), qsort_compare);
    qsort(right_col, INPUT_LINES_COUNT, sizeof(unsigned int), qsort_compare);

    unsigned int sums[INPUT_LINES_COUNT];
    unsigned int multiplied_sums[INPUT_LINES_COUNT];
    for (unsigned int i = 0; i < INPUT_LINES_COUNT; i++) {

        unsigned int diff = abs((int)left_col[i] - (int)right_col[i]);
        sums[i] = diff;

        unsigned int factor = 0; 
        find(multipliers, left_col[i], &factor);
        multiplied_sums[i] = left_col[i] * factor;
    }

    unsigned int sum = 0;
    unsigned int sum_with_factors = 0;
    for (unsigned int i = 0; i < INPUT_LINES_COUNT; i++) {
        sum += sums[i];
        sum_with_factors += multiplied_sums[i];
    }

    printf("Part 1 solution is: %u\nPart 2 solution is: %u\n", sum, sum_with_factors);
}

static int qsort_compare(const void *a, const void *b) {
    return *(unsigned int *)a - *(unsigned int *)b;
}











