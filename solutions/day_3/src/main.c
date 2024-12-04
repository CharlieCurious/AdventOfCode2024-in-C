#include <collections.h>
#include <file_parser.h>
#include <mul_finder.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = open_input_file("input_files/day_3.txt");
    if (!file) {
        perror("Could not open input file.");
        exit(EXIT_FAILURE);
    }

    InputLines *input_lines = read_input_lines(file);
    if (!input_lines) exit(EXIT_FAILURE);

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *program = malloc(file_size + 1);
    fread(program, 1, file_size, file);
    program[file_size] = '\0';

    char *program_with_enabled_sections = remove_substring(program);
    if (!program_with_enabled_sections) exit(EXIT_FAILURE);

    const char *instruction_pattern = "mul\\([0-9]{1,3},[0-9]{1,3}\\)";

    ListString *part_1_instr = find_instructions(program, instruction_pattern); 
    if (!part_1_instr) exit(EXIT_FAILURE);

    ListString *part_2_instr = find_instructions(program_with_enabled_sections, instruction_pattern); 
    if (!part_2_instr) exit(EXIT_FAILURE);

    unsigned int part_1_sum = process_mul_instruction(part_1_instr);
    unsigned int part_2_sum = process_mul_instruction(part_2_instr);

    printf("Part 1: %u\nPart 2: %u\n", part_1_sum, part_2_sum);

    return EXIT_SUCCESS;
}
