#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expand.h"

void expand_variables(pipeline_t *pipeline)
{
    for (int i = 0; i < pipeline->command_count; i++)
    {
        for (int j = 0; j < pipeline->commands[i].argc; j++)
        {
            char *arg = pipeline->commands[i].argv[j];

            if (arg[0] == '$')
            {
                char *value = getenv(arg + 1);

                if (value != NULL)
                {
                    pipeline->commands[i].argv[j] = value;
                }
            }
        }
    }
}
