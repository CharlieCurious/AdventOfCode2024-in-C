#pragma once

#define OBSTRUCTION '#'
#define GUARD '^'
#define VISITED 'X'
#define PRINTER 'O'

#include <path_tracer.h>
#include <stddef.h>
#include <sys/types.h>

typedef struct Grid {
    size_t width;
    size_t height;
    char **map;
} Grid;

void print_grid(Grid *grid, uint sum); 
uint follow_line_west(Grid *grid, Step step, uint sum);
uint follow_line_east(Grid *grid, Step step, uint sum);
uint follow_col_north(Grid *grid, Step step, uint sum);
uint follow_col_south(Grid *grid, Step step, uint sum);
void sum_and_check_if_not_yet_visited(char **checked, size_t x, size_t y, uint *sum);
