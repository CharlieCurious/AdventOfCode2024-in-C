#include <permutations.h>
#include <stdlib.h>
#include <string.h>

void permutations_generate(
        char **permutations, 
        size_t *count, 
        char *slots, 
        uint n, 
        uint index) {

    if (index == n) {
        permutations[*count] = (char *)malloc((n + 1) * sizeof(char));
        strncpy(permutations[*count], slots, n);
        permutations[*count][n] = '\0';
        (*count)++;
        return;
    }

    slots[index] = '+';
    permutations_generate(permutations, count, slots, n, index + 1);

    slots[index] = '*';
    permutations_generate(permutations, count, slots, n, index + 1);
}
