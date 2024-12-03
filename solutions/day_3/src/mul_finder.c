#include <mul_finder.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compile_regex(regex_t *regex);

ListString *find_mul_instructions(const char *program, const unsigned int program_length) {
    regex_t regex;
    regmatch_t match;
    unsigned int start_index = 0;
    int result; // holds the results of regex operations.

    result = compile_regex(&regex);
    if (result != 0) {
        perror("Failed to compile regex");
        return NULL;
    }

    char **found_instructions = (char **)calloc(program_length, sizeof(char *));
    if (!found_instructions) {
        perror("Failed to allocate for found_instructions");
        regfree(&regex);
        return NULL;
    }

    while ((result = regexec(&regex, program + start_index, 1, &match, 0)) == 0) {
        int match_start = start_index + match.rm_so;
        int match_end = start_index + match.rm_eo;

        unsigned int size = match_end - match_start;

        char *found_instruction = (char *)malloc(size + 1);
        if (!found_instruction) {
            perror("Failed to allocate for found instruction");
            regfree(&regex);
            free(found_instructions);
            return NULL;
        }

        strncpy(found_instruction, program + match_start, size); 
        found_instruction[size] = '\0';

        start_index += match.rm_eo + 1;
    }

    return NULL;

}

unsigned int process_mul_instruction(const char *instruction) {
    return 0;
}

static int compile_regex(regex_t *regex) {
    const char *pattern = "mul\\([0-9]+,[0-9]+\\)";
    return regcomp(regex, pattern, REG_EXTENDED);
}
