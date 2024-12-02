#include <banalyser.h>
#include <file_parser.h>
#include <stdlib.h>

int main() {
    FILE *file = open_input_file("input_files/day_2.txt");
    if (!file) exit(EXIT_FAILURE); 
    
    InputLines *input_lines = read_input_lines(file);
    if (!input_lines) exit(EXIT_FAILURE);

    fclose(file);

    unsigned int safe_report_count = 0;
    unsigned int safe_damped_report_count = 0;
    for (unsigned int i = 0; i < input_lines->count; i++) {
        unsigned int report_size = get_report_size(input_lines->lines[i]);
        unsigned int *report = parse_report(input_lines->lines[i], report_size);

        if (is_report_safe(report, report_size))
            safe_report_count++;

        if(check_with_removed_element(report, report_size))
            safe_damped_report_count++;

        free(report);
    }

    free_input_lines(&input_lines); 

    printf("Solution for part 1: %u\nSolution for part 2: %u\n", 
            safe_report_count, 
            safe_damped_report_count);
}
