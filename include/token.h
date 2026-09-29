#ifndef TOKEN_H
#define TOKEN_H

#define MAX_TOKENS 128

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE
} token_type_t;

typedef struct {
    token_type_t type;
    char *value;
} token_t;

typedef struct {
    token_t tokens[MAX_TOKENS];
    int count;
} token_list_t;

void token_print(token_list_t *list);
void free_tokens(token_list_t *list);

#endif
