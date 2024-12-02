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

bool is_report_safe_part_2(unsigned int *numbers, unsigned int length) {

    unsigned int previous = numbers[0];
    bool error_damped = false;
    bool is_increasing = numbers[0] < numbers[1];
    for (int i = 1; i < length; i++) {
        if (is_increasing && numbers[i] < previous) {
            if (error_damped) return false;
            error_damped = true;
            is_increasing = false;
            previous = numbers[i];
            continue;
        }
        if (!is_increasing && numbers[i] > previous) {
            if (error_damped) return false;
            error_damped = true;
            is_increasing = true;
            previous = numbers[i];
            continue;
        }
        if (abs((int)numbers[i] - (int)previous) > 3 || numbers[i] == previous) {
            if (error_damped) return false;
            error_damped = true;
            continue;
        }
        previous = numbers[i];
    }

    return true;
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
