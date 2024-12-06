#include <setjmp.h>
#include <updates.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int *parse_update(const char *update);

static jmp_buf exception;
 
unsigned int **parse_updates_str(const char *updates_str, unsigned int num_updates) { 
    unsigned int **updates = (unsigned int**)malloc(num_updates * sizeof(unsigned int *));
    if (!updates) {
        perror("Failed to allocate for updates");
        return NULL;
    }

    char *updates_str_copy = strdup(updates_str);
    if (!updates_str_copy) {
        perror("Failed to duplicate updates_str");
        free(updates);
        return NULL;
    }

    if (setjmp(exception)) {
        free(updates);
        free(updates_str_copy);
        return NULL;
    }

    char *tokptr1;  // needed because normal strtok maintais global state! nice find!
    char *line = strtok_r(updates_str_copy, "\n", &tokptr1);
    unsigned int line_index = 0;
    while (line) {
        updates[line_index] = parse_update(line);

        line = strtok_r(NULL, "\n", &tokptr1);
        line_index++;
    }

    free(updates_str_copy);
    return updates;
}

static unsigned int *parse_update(const char *update_line) {
    // Number of elements per update varies
    size_t count = 0;
    const char *tmp = update_line;
    while(*tmp) {
        if (*tmp == ',')
            count++;
        tmp++;
    }
    count++;

    unsigned int *page_numbers = (unsigned int *)malloc(count * sizeof(unsigned int));
    if (!page_numbers) {
        perror("Failed to allocate for page_numbers");
        longjmp(exception, 0);
    }

    size_t index = 0;
    char *update_copy = strdup(update_line); // copy because update_line is const and strtok modifies
    if (!update_copy) {
        perror("Failed to allocate for update_copy");
        free(page_numbers);
        longjmp(exception, 0);
    }

    char *tokptr2;
    char *token = strtok_r(update_copy, ",", &tokptr2);
    while (token) {
        page_numbers[index++] = (unsigned int)strtoul(token, NULL, 10);
        token = strtok_r(NULL, ",", &tokptr2);
    }

    free(update_copy);
    return page_numbers;
}
