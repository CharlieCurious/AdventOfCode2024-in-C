#include <banalyser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int *parse_report(char *report, unsigned int size) {
    unsigned int *buffer = (unsigned int *)malloc(sizeof(unsigned int) * size);
    if (!buffer) {
        perror("Failed to allocate for parsing report");
        return NULL;
    }

    size_t index = 0;
    char *token = strtok(report, " \n");
    while (token != NULL && index < size) {
        buffer[index++] = (unsigned int)atoi(token);
        token = strtok(NULL, " \n");
    }

    return buffer;
}

bool is_report_safe(unsigned int *numbers, unsigned int length) {

    unsigned int previous = numbers[0];
    unsigned int strikes = 0;
    bool is_increasing = numbers[0] < numbers[1];
    for (int i = 1; i < length; i++) {
        if (abs((int)numbers[i] - (int)previous) > 3 || numbers[i] == previous) {
            return false;
        }
        if (is_increasing && numbers[i] < previous) {
            return false;
        }
        if (!is_increasing && numbers[i] > previous) {
            return false;
        }
        previous = numbers[i];
    }

    return true;
} 

bool check_with_removed_element(unsigned int *data, unsigned int length) {
    for (int i = 0; i < length; i++) {

        unsigned int *data_copy = (unsigned int *)malloc((length - 1) * sizeof(unsigned int));

        if (data_copy == NULL)
            return false;

        memcpy(data_copy, data, i * sizeof(int));
        memcpy(data_copy + i, data + i + 1, (length - i - 1) * sizeof(int));

        if (is_report_safe(data_copy, length - 1)) {
            free(data_copy); 
            return true;
        }

        free(data_copy);
    }
    return false;
}

unsigned int get_report_size(char *report) {
    unsigned int count = 0;
    const char *ptr = report;

    while (*ptr != '\0') {
        if ((*ptr >= '0' && *ptr <= '9') && 
                (ptr == report || *(ptr - 1) == ' ' || *(ptr - 1) == '\n')) {
            count++;
        }
        ptr++;
    }

    return count;
}
