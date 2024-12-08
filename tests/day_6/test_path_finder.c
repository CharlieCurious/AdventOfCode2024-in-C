#include "unity_internals.h"
#include <path_finder.h>
#include <stdio.h>
#include <unity.h>
#include <stdlib.h>

char test_map[10][10] = {
    { '.', '.', '.', '.', '#', '.', '.', '.', '.', '.' },
    { '.', '.', '.', '.', '.', '.', '.', '.', '.', '#' },
    { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.' },
    { '.', '.', '#', '.', '.', '.', '.', '.', '.', '.' },
    { '.', '.', '.', '.', '.', '.', '.', '#', '.', '.' },
    { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.' },
    { '.', '#', '.', '.', '^', '.', '.', '.', '.', '.' },
    { '.', '.', '.', '.', '.', '.', '.', '.', '#', '.' },
    { '#', '.', '.', '.', '.', '.', '.', '.', '.', '.' },
    { '.', '.', '.', '.', '.', '.', '#', '.', '.', '.' }
};

char expected_end_map[10][10] = {
    "....#.....", 
    "....XXXXX#", 
    "....X...X.", 
    "..#.X...X.", 
    "..XXXXX#X.", 
    "..X.X.X.X.", 
    ".#XXXXXXX.", 
    ".XXXXXXX#.", 
    "#XXXXXXX..", 
    "......#X..",
};

Grid *grid;

void setUp() {
    grid = (Grid *)malloc(10 * sizeof(char *));
    grid->width = 10;
    grid->height = 10;
    grid->map = (char **)malloc(10 * sizeof(char *));
    
    for (size_t i = 0; i < grid->height; i++) {
        grid->map[i] = (char *)malloc(10 * sizeof(char));
        for (size_t j = 0; j < 10; j++) {
            grid->map[i][j] = test_map[i][j];
        }
    }
}

void should_sum_and_check_if_not_yet_visited() {
    char map[2][2] = {
        { '.', VISITED },
        { '.', '.' } };

    char **map_ref = malloc(2 * sizeof(char *));
    map_ref[0] = map[0];
    map_ref[1] = map[1];

    uint sum = 0;

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            sum_and_check_if_not_yet_visited(map_ref, i, j, &sum);
        }
    }

    TEST_ASSERT_EQUAL_UINT_MESSAGE(3, sum, "Assert sum is correct");

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            char message[40];
            snprintf(message, sizeof(message), "Assert [%zu][%zu] marked visited", i, j);
            TEST_ASSERT_EQUAL_CHAR_MESSAGE(VISITED, map_ref[i][j], message);
        }
    }

    free(map_ref);
}

void should_follow_path_and_sum_correctly() {
    uint sum = follow_col_north(grid, 6, 4, 0);
    for (size_t i = 0; i < grid->height; i++) {
        for (size_t j = 0; j < grid->width; j++) {
            printf("%c ", grid->map[i][j]); // Print each character with a space
        }
        printf("\n"); // Newline after each row
    }

    TEST_ASSERT_EQUAL_UINT_MESSAGE(41, sum, "Assert right sum");
}

void should_mark_correct_path_as_visited() {
    uint sum = follow_col_north(grid, 6, 4, 0);
    for (size_t x = 0; x < 10; x++) {
        char message[40];
        snprintf(message, sizeof(message), "Assert line [%zu] marked visited", x);
        TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(expected_end_map[x], grid->map[x], 10, message);
    }
}

void tearDown() {
    if (!grid)
        return;

    for (size_t i = 0; i < grid->height; i++) {
        free(grid->map[i]);
    }
    free(grid->map);
    free(grid);
    grid = NULL;
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_sum_and_check_if_not_yet_visited);
    RUN_TEST(should_follow_path_and_sum_correctly);
    RUN_TEST(should_mark_correct_path_as_visited);
    return UNITY_END();
}
