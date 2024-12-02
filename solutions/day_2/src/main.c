#include <file_parser.h>
#include <stdlib.h>

int main() {
    FILE *file = open_input_file("input_files/day_2.txt");
    if (!file) exit(EXIT_FAILURE); 
    
    InputLines *input_lines = read_input_lines(file);
    if (!input_lines) exit(EXIT_FAILURE);


    free_input_lines(&input_lines); 
}
