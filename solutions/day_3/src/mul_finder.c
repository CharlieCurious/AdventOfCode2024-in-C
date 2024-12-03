#include <collections.h>
#include <mul_finder.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListString *find_patterns(const char *text, const char *pattern) {
    regex_t regex;
    regmatch_t match;
    unsigned int start_index = 0;
    int result; // holds the results of regex operations.
    
    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        perror("Failed to compile regex");
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

ListString *find_enabled_sections(const char *string) {
    const char *pattern = "do\\(\\)([^d]*)(don't\\(\\)|$)";

    ListString *enabled_sections = find_patterns(string, pattern);

    return enabled_sections;
}

unsigned int process_mul_instruction(ListString *instructions) {

    const char *pattern = "[0-9]{1,3}";
    unsigned int sum_of_instructions = 0;

    for (size_t i = 0; i < instructions->size; i++) {
        ListString *numbers = find_patterns(instructions->strings[i], pattern);
        sum_of_instructions += atoi(numbers->strings[0]) * atoi(numbers->strings[1]);
        free_list_str(&numbers);
    }

    return sum_of_instructions;
}
