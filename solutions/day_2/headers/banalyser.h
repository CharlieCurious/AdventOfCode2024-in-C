#pragma once

#include <stdbool.h>

unsigned int *parse_report(char *report, unsigned int size);

bool is_report_safe(unsigned int *numbers, unsigned int length);
bool check_with_removed_element(unsigned int *numbers, unsigned int length);
unsigned int get_report_size(char *report);

