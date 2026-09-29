#include <stdio.h>
#include <stdlib.h>
#include "token.h"

void token_print(token_list_t *list)
{
    printf("Tokens:\n");

    for (int i = 0; i < list->count; i++)
    {
        printf("  [%d] %s\n", i, list->tokens[i].value);
    }
}

void free_tokens(token_list_t *list)
{
    for (int i = 0; i < list->count; i++)
    {
        free(list->tokens[i].value);
        list->tokens[i].value = NULL;
    }

    list->count = 0;
}
