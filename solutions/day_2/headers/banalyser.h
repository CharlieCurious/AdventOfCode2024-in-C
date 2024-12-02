#pragma once

#include <stdbool.h>

unsigned int *parse_report(char *report, unsigned int size);

bool is_report_safe(unsigned int *numbers, unsigned int length);

bool is_report_safe_part_2(unsigned int *numbers, unsigned int length);

unsigned int get_report_size(char *report);

