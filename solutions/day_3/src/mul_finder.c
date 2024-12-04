#include <collections.h>
#include <mul_finder.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListString *find_instructions(const char *text, const char *pattern) {
    regex_t regex;
    regmatch_t match;
    unsigned int start_index = 0;
    int result; // holds the results of regex operations.
    
    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        fprintf(stderr,"Failed to compile regex for pattern: %s\n", pattern);
        return NULL;
    }

    ListString *found_instructions = create_list_str(10);
    if (!found_instructions) {
        perror("Failed to allocate for found_instructions");
        regfree(&regex);
        return NULL;
    }

    while ((result = regexec(&regex, text + start_index, 1, &match, 0)) == 0) {
        int match_start = start_index + match.rm_so;
        int match_end = start_index + match.rm_eo;

        unsigned int size = match_end - match_start;

        char found_instruction[size];

        strncpy(found_instruction, text + match_start, size); 
        found_instruction[size] = '\0';

        append_list_str(found_instructions, found_instruction);

        start_index += match.rm_eo;
    }

    return found_instructions;
}

char *remove_substring(const char *string) {
    size_t length = strlen(string);
    char *output = (char *)malloc(length + 1);
    if (!output) {
        perror("Failed to allocate for remove_substring");
        return NULL;
    }

    bool enabled = true;
    const char *current = string;
    char *out_ptr = output;

    while(*current) {
        if (strncmp(current, "don't()", 7) == 0) {
            enabled = false;
            current += 7;
        } else if (strncmp(current, "do()", 4) == 0) {
            enabled = true;
            current += 4;
        } else {
            if (enabled) {
                *out_ptr++ = *current;
            }
            current++;
        }
    }
    *out_ptr = '\0';

    // Adjust size
    char *shrinked_output = realloc(output, strlen(output) + 1);
    if (shrinked_output)
        return shrinked_output;
    else
        return output;

}

unsigned int process_mul_instruction(ListString *instructions) {

    const char *pattern = "[0-9]{1,3}";
    unsigned int sum_of_instructions = 0;

    for (size_t i = 0; i < instructions->size; i++) {
        ListString *numbers = find_instructions(instructions->strings[i], pattern);
        sum_of_instructions += atoi(numbers->strings[0]) * atoi(numbers->strings[1]);
        free_list_str(&numbers);
    }

    return sum_of_instructions;
}
