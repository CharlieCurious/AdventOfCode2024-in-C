#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define INPUT_LINE_LEN 50
#define INPUT_LINES_COUNT 50
#define MAX_TYPES_OF_SYMBOLS 100

static void process_char(char ch, size_t x, size_t y);

int main() {
    FILE *file = fopen("input_files/day_8.txt", "r");    
    if (!file) {
        perror("Could not open input file");
        return EXIT_FAILURE;
    }
    
    char buffer[INPUT_LINE_LEN + 1];
    size_t line = 0;
    while (fgets(buffer, sizeof(buffer), file) && line < INPUT_LINES_COUNT) {
        char *ptr = buffer;
        size_t col = 0;
        while (*ptr != '\0') {
            process_char(*ptr, line, col);
        }
    }

    
    return EXIT_SUCCESS;
}

static void process_char(char ch, size_t x, size_t y) {
}
