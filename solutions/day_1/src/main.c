#include <dictionary.h>
#include <file_parser.h>
#include <min_heap.h>
#include <stdlib.h>

int main() {
    FILE *file = open_input_file("input_files/day_1.txt"); 
    if (file == NULL) exit(EXIT_FAILURE);

    InputLines *input_lines = (InputLines *)malloc(sizeof(InputLines));
    read_input_lines(file, input_lines);
    fclose(file);

    // wdf did I use min heaps?! shouldn've just sorted...
    MinHeap *left_col = create_min_heap(1000);
    MinHeap *right_col = create_min_heap(1000);
    Dictionary *multipliers = create_dictionary(1000);

    for (unsigned int i = 0; i < input_lines->count; i++) {
        unsigned int left_num, right_num;
        sscanf(input_lines->lines[i], "%u %u", &left_num, &right_num);

        insert(left_col, left_num);
        insert(right_col, right_num);

        unsigned int occurence_count = 0;
        find(multipliers, right_num, &occurence_count);
        insert_in_dictionary(multipliers, right_num, ++occurence_count);
    }

    unsigned int sums[1000];
    unsigned int multiplied_sums[1000];
    for (unsigned int i = 0; i < 1000; i++) {
        unsigned int left_num = pop_min(left_col);

        unsigned int diff = abs((int)left_num - (int)pop_min(right_col));
        sums[i] = diff;

        unsigned int factor = 0; 
        find(multipliers, left_num, &factor);
        multiplied_sums[i] = left_num * factor;
    }

    unsigned int sum = 0;
    unsigned int sum_with_factors = 0;
    for (unsigned int i = 0; i < 1000; i++) {
        sum += sums[i];
        sum_with_factors += multiplied_sums[i];
    }

    printf("Part 1 solution is: %u\n. Part 2 solution is: %u\n", sum, sum_with_factors);

}
