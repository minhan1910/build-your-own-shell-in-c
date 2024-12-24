#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "string_util.h"

#define DEFAULT_BUFFER_SIZE 2

char * read_line() {
    int ch;
    size_t allocated_size = DEFAULT_BUFFER_SIZE;
    char *buffer = (char *)malloc(allocated_size);

    if (buffer == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }

    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (i == allocated_size) {
            allocated_size *= 2;
            char * new_buffer = realloc(buffer, allocated_size * 2);
            if (new_buffer == NULL) {
                perror("New buffer failed");
                free(buffer);
                exit(1);
            }
            buffer = new_buffer;
        }
        buffer[i++] = ch;
    }

    buffer[i] = '\0';

    return buffer;
}

int count_token(const char * str, const char * delimiter) {
    char * tmp = strdup(str);
    if (tmp == NULL) {
        perror("Allocate tmp failed");
        return -1;
    }

    int count = 0;

    char * token = strtok(tmp, delimiter);
    while (token != NULL) {
        ++count;
        token = strtok(NULL, delimiter);
    }

    free(tmp);
    return count;
}

char ** split_str(const char * str, const char * delimiter, int * count) {
    if (!str || !delimiter) {
        return NULL;
    }

    int tokens = count_token(str, delimiter);
    if (tokens == -1) {
        return NULL;
    }

    char * str_copy = strdup(str);
    if (str_copy == NULL) {
        perror("Allocate 'str_copy' to split_str failed");
        return NULL;
    }

    char ** result = malloc((tokens + 1) * sizeof(char*));
    if (result == NULL) {
        perror("Allocate 'result' in split_str failed");
        free(str_copy);
        return NULL;
    }

    int j = 0;
    char * token = strtok(str_copy, delimiter);
    while (token != NULL) {
        result[j] = strdup(token);
        if (result[j] == NULL) {
            for (int i = 0; i < j; ++i) {
                free(result[i]);
            }
            free(result);
            free(str_copy);
            return NULL;
        }
        ++j;
        token = strtok(NULL, delimiter);
    }

    result[j] = NULL;

    if (count) {
        *count = tokens;
    }

    free(str_copy);

    return result;
}

void free_strs(char ** tokens) {
    if (tokens == NULL) {
        return;
    }
    for (int i = 0; tokens[i] != NULL; ++i) {
        free(tokens[i]);
    }
    free(tokens);
}