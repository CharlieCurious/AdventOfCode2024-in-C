#include <collections.h>
#include <file_parser.h>
#include <mul_finder.h>
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

    char *content = malloc(file_size + 1);
    fread(content, 1, file_size, file);
    content[file_size] = '\0';

    char *instruction_pattern = "mul\\([0-9]{1,3},[0-9]{1,3}\\)";
    ListString *instructions = find_patterns(content, instruction_pattern);
    unsigned int part_one = process_mul_instruction(instructions);

    printf("Part 1 solution: %u\n", part_one);

}
