#include <collections.h>
#include <setjmp.h>
#include <updates.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ListUInt *parse_update(const char *update);

static jmp_buf exception;
 
UpdateList *parse_updates_str(const char *updates_str, unsigned int num_updates) { 
    UpdateList *updates = (UpdateList *)malloc(sizeof(UpdateList));
    ListUInt **individual_updates = (ListUInt **)malloc(num_updates * sizeof(ListUInt *));
    if (!updates || !individual_updates) {
        perror("Failed to allocate for updates");
        return NULL;
    }

    updates->updates = individual_updates;

    char *updates_str_copy = strdup(updates_str);
    if (!updates_str_copy) {
        perror("Failed to duplicate updates_str");
        free(updates);
        free(individual_updates);
        return NULL;
    }

    if (setjmp(exception)) {
        free(updates);
        free(updates_str_copy);
        return NULL;
    }

    char *tokptr1;  // needed because normal strtok maintais global state! nice find!
    char *line = strtok_r(updates_str_copy, "\n", &tokptr1);
    updates->num_updates = 0;
    while (line) {
        updates->updates[updates->num_updates++] = parse_update(line);
        line = strtok_r(NULL, "\n", &tokptr1);
    }

    free(updates_str_copy);
    return updates;
}

void free_update_list(UpdateList **update_list) {
    if (update_list == NULL || *update_list == NULL)
        return;

    if ((*update_list)->updates != NULL) {
        for (size_t i = 0; i < (*update_list)->num_updates; i++) {
            free_list_uint(&(*update_list)->updates[i]);
        }
        free((*update_list)->updates);
        (*update_list)->updates = NULL;
    }

    free(*update_list);
    *update_list = NULL;
}


static ListUInt *parse_update(const char *update_line) {
    ListUInt *list = create_list_uint(3);
    if (!list) {
        perror("Failed to allocate for page_numbers");
        longjmp(exception, 0);
    }

    size_t index = 0;
    char *update_copy = strdup(update_line); // copy because update_line is const and strtok modifies
    if (!update_copy) {
        perror("Failed to allocate for update_copy");
        free_list_uint(&list);
        longjmp(exception, 0);
    }

    char *tokptr2;
    char *token = strtok_r(update_copy, ",", &tokptr2);
    while (token) {
        uint page_number = (unsigned int)strtoul(token, NULL, 10);
        append_list_uint(list, page_number);
        token = strtok_r(NULL, ",", &tokptr2);
    }

    free(update_copy);
    return list;
}
