#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static char *my_strdup(const char *s)
{
    char *copy = malloc(strlen(s) + 1);

    if (copy == NULL)
        return NULL;

    strcpy(copy, s);
    return copy;
}

void lexer(const char *line, token_list_t *tokens)
{
    tokens->count = 0;

    char *copy = my_strdup(line);

    if (copy == NULL)
        return;

    char *word = strtok(copy, " \t");

    while (word != NULL && tokens->count < MAX_TOKENS)
    {
        tokens->tokens[tokens->count].value = my_strdup(word);

        if (strcmp(word, "|") == 0)
            tokens->tokens[tokens->count].type = TOKEN_PIPE;
        else
            tokens->tokens[tokens->count].type = TOKEN_WORD;

        tokens->count++;
        word = strtok(NULL, " \t");
    }

    free(copy);
}
