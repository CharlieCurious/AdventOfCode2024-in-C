#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *read_input_to_str(char *file_name);

int main() {
    char *input_str = read_input_to_str("input_files/day_5.txt");

    char *token = strstr(input_str, "\n\n");
    size_t rules_len = token - input_str;

    char *rules_str = (char *)malloc((rules_len + 1) * sizeof(char));
    if (!rules_str) {
        perror("Failed to allocate for rules_str");
        return EXIT_FAILURE;
    }

    strncpy(rules_str, input_str, rules_len);
    rules_str[rules_len] = '\0';

    char *updates_str = (char *)malloc((strlen(token + 2) + 1) * sizeof(char));
    if (!rules_str) {
        perror("Failed to allocate for updates_str");
        return EXIT_FAILURE;
    }
    strcpy(updates_str, token + 2);

    free(input_str);
    free(rules_str);
    free(updates_str);
    return EXIT_SUCCESS;
}

char *read_input_to_str(char *file_name) {

    FILE *file = fopen(file_name, "r");
    if (!file) {
        perror("Could not open input file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc((file_size + 1) * sizeof(char));
    if (!buffer) {
        perror("Failed to allocate for input string buffer");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    fclose(file);

    return buffer;
}