#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rules.h>

#define LINE_ALLOC_EX 1
#define LINE_PARSING_EX 2

static void insert_rule(rules_graph graph, char *rule);

static jmp_buf exception;

rules_graph init_rules_graph(char *rules_str, unsigned int max_page_number) {

    // increase by one because we want idexes from 0 to max_page_number.
    // there should be an option for [max][some_number]
    max_page_number++;

    rules_graph graph = (rules_graph)calloc(max_page_number, sizeof(bool *));
    if (!graph) {
        perror("Failed to allocate for rules_graph");
        return NULL;
    }

    int exception_code;
    if ((exception_code = setjmp(exception))) {
       if (exception_code == LINE_ALLOC_EX)
           perror("Failed to allocate memory of graph row");
       if (exception_code == LINE_PARSING_EX)
           perror("Failed to parse rule");
       return NULL;
    } else {
        for(unsigned int i = 0; i < max_page_number; i++) {
            graph[i] = (bool *)calloc(max_page_number, sizeof(bool *));
            if(!graph[i]) 
                longjmp(exception, LINE_ALLOC_EX);
        }

        char *line = strtok(rules_str, "\n");
        while (line != NULL) {
            insert_rule(graph, line);        
            line = strtok(NULL, "\n");
        }
    }

    return graph;
}

bool contains_rule(rules_graph graph, unsigned int first, unsigned int next) {
    return graph[first][next];
}

static void insert_rule(rules_graph graph, char *rule) {
    unsigned int first, next;
    int rule_parsing_result = sscanf(rule, "%u|%u", &first, &next);

    if (rule_parsing_result != 2) {
        longjmp(exception, rule_parsing_result);
    }

    graph[first][next] = true;
}

