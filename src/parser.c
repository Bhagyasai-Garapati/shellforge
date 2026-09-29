#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int parser(token_list_t *tokens, pipeline_t *pipeline)
{
    pipeline->command_count = 0;

    if (tokens->count == 0)
        return 0;

    int command_index = 0;
    int arg_index = 0;

    pipeline->command_count = 1;

    for (int i = 0; i < tokens->count; i++)
    {
        if (tokens->tokens[i].type == TOKEN_PIPE)
        {
            if (arg_index == 0)
                return 0;

            pipeline->commands[command_index].argv[arg_index] = NULL;

            command_index++;

            if (command_index >= MAX_COMMANDS)
                return 0;

            pipeline->command_count++;
            arg_index = 0;
        }
        else
        {
            if (arg_index >= MAX_ARGS - 1)
                return 0;

            pipeline->commands[command_index].argv[arg_index] =
                tokens->tokens[i].value;

            arg_index++;
            pipeline->commands[command_index].argc = arg_index;
        }
    }

    pipeline->commands[command_index].argv[arg_index] = NULL;

    return 1;
}

void pipeline_print(pipeline_t *pipeline)
{
    printf("Pipeline:\n");

    for (int i = 0; i < pipeline->command_count; i++)
    {
        printf("  Command %d:", i + 1);

        for (int j = 0; j < pipeline->commands[i].argc; j++)
        {
            printf(" %s", pipeline->commands[i].argv[j]);
        }

        printf("\n");
    }
}

void free_pipeline(pipeline_t *pipeline)
{
    pipeline->command_count = 0;
}
