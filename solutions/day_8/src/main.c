#include <list_dict.h>
#include <algorithm.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define INPUT_LINE_LEN 50
#define INPUT_LINES_COUNT 50
#define MAX_TYPES_OF_SYMBOLS 100

static void process_char(char ch, size_t x, size_t y, AnthenasDictionary *dict);

int main() {
    FILE *file = fopen("input_files/day_8.txt", "r");    
    if (!file) {
        perror("Could not open input file");
        return EXIT_FAILURE;
    }

    AnthenasDictionary *anthenas = dictionary_create(INPUT_LINE_LEN * INPUT_LINES_COUNT);
    
    char buffer[INPUT_LINE_LEN + 1];
    size_t line = 0;
    while (fgets(buffer, sizeof(buffer), file) && line < INPUT_LINES_COUNT) {
        char *ptr = buffer;
        size_t col = 0;
        while (*ptr != '\0') {
            process_char(*ptr, line, col, anthenas);
        }
    }

    KeyValue kvps[anthenas->capacity];
    size_t out_anthenas_count;
    dictionary_get_all_kvp(anthenas, kvps, &out_anthenas_count);
    
    dictionary_free(anthenas);
    return EXIT_SUCCESS;
}

static void process_char(char ch, size_t x, size_t y, AnthenasDictionary *dict) {
    if (ch == '.')
        return;

    Location location;
    location.x = x;
    location.y = y;
    
    dictionary_insert(dict, ch, location);
}
