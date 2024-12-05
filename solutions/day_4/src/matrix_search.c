#include <matrix_search.h>
#include <string.h>
#include <stdlib.h>

char **get_compass_rose(InputLines *input_lines, int line, int column) {
    char **matrix = input_lines->lines;
    size_t width = strlen(matrix[0]);
    size_t height = input_lines->count;
    char center = matrix[line][column];

    char **winds = (char **)calloc(9, sizeof(char *)); // 9 to include NULL termination
                                                       
    
    // get west
    if (column - 3 >= 0) {
        char west[4] = { center, matrix[line][column-1], matrix[line][column-2], matrix[line][column-3] };
        winds[6] = strndup(west, 4);
    }

    // get east
    if (column + 3 < width) {
        char east[4] = { center, matrix[line][column+1], matrix[line][column+2], matrix[line][column+3] };
        winds[2] = strndup(east, 4);
    }
    
    if (line >= 3) {
        char north[4] = { center, matrix[line-1][column], matrix[line-2][column], matrix[line-3][column] };
        winds[0] = strndup(north, 4);
        
        if (column + 3 < width) {
            char north_east[4] = { center, matrix[line-1][column+1], matrix[line-2][column+2], matrix[line-3][column+3] };
            winds[1] = strndup(north_east, 4);

        }

        if (column - 3 >= 0) {
            char north_west[4] = { center, matrix[line-1][column-1], matrix[line-2][column-2], matrix[line-3][column-3] };
            winds[7] = strndup(north_west, 4);

        }
    }
    if (line + 3 < height) {
        char south[4] = { center, matrix[line+1][column], matrix[line+2][column], matrix[line+3][column] };
        winds[4] = strndup(south, 4);

        if (column + 3 < width) {
            char south_east[4] = { center, matrix[line+1][column+1], matrix[line+2][column+2], matrix[line+3][column+3] };
            winds[3] = strndup(south_east, 4);
        }

        if (column - 3 >= 0) {
            char south_west[4] = { center, matrix[line+1][column-1], matrix[line+2][column-2], matrix[line+3][column-3] };
            winds[5] = strndup(south_west, 4);
        }
    }

    return winds;
}
